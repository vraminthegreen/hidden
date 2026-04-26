#include "Game.h"
#include <cmath>

Game::Game() : running(true), state(GameState::PREPARATION) {
    minerals = 100;
    ki = 50;
    energy = 50;
    maxEnergy = 100;
    currentWave = 1;

    enemiesToSpawn = 0;
    spawnTimer = 0.0f;
    spawnDelay = 2.0f;

    activeBlueprint.id = "skeleton";
    activeBlueprint.name = "Basic Skeleton";
    activeBlueprint.healthBonus = 30;
    activeBlueprint.damageBonus = 10;
    activeBlueprint.mineralCost = 10;
    activeBlueprint.kiCost = 5;
}

Game::~Game() {
}

void Game::Init() {
    map.Init();
    ui.Init();

    eye = std::make_unique<Eye>(map.GetEyePos());
}

void Game::UpdateWaveSpawning() {
    if (enemiesToSpawn > 0) {
        spawnTimer += GetFrameTime();
        if (spawnTimer >= spawnDelay) {
            spawnTimer = 0.0f;
            auto enemy = std::make_unique<Enemy>(map.GetSpawnPos(), map.GetPath());
            enemy->Init();
            enemies.push_back(std::move(enemy));
            enemiesToSpawn--;
        }
    } else if (enemies.empty() && state == GameState::COMBAT) {
        state = GameState::REWARD;
        rewardSystem.GenerateChoices();
        minions.clear(); // Clear surviving minions at wave end for simplicity
    }
}

void Game::HandleHandOfPower() {
    if (Input::IsLightningStrikePressed()) {
        Vector2 mousePos = Input::GetMousePos();
        int gridX = mousePos.x / TILE_SIZE;
        int gridY = mousePos.y / TILE_SIZE;

        Int2 targetPos = {gridX, gridY};

        if (IsInPowerRange(targetPos) && energy >= lightningCost) {
            bool hitEnemy = false;
            for (auto& enemy : enemies) {
                if (enemy->GetPos() == targetPos) {
                    enemy->TakeDamage(lightningDamage);
                    hitEnemy = true;
                    break;
                }
            }

            if (hitEnemy) {
                energy -= lightningCost;
                lightningEffects.push_back({mousePos, 0.5f});
            }
        }
    }
}

void Game::HandleMinionSpawning() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = Input::GetMousePos();
        int gridX = mousePos.x / TILE_SIZE;
        int gridY = mousePos.y / TILE_SIZE;

        Int2 spawnPos = {gridX, gridY};

        if (map.GetTile(gridX, gridY) == TileType::PATH && IsInPowerRange(spawnPos) &&
            minerals >= activeBlueprint.mineralCost && ki >= activeBlueprint.kiCost) {

            bool slotTaken = false;
            for (const auto& minion : minions) {
                if (minion->GetPos() == spawnPos) {
                    slotTaken = true;
                    break;
                }
            }

            if (!slotTaken) {
                minerals -= activeBlueprint.mineralCost;
                ki -= activeBlueprint.kiCost;
                auto minion = std::make_unique<Minion>(spawnPos, activeBlueprint);
                minion->Init();
                minions.push_back(std::move(minion));
            }
        }
    }
}

void Game::ApplyReward(const Reward& reward) {
    if (reward.type == RewardType::RESOURCES) {
        minerals += 50;
        ki += 20;
    } else if (reward.type == RewardType::MAX_ENERGY) {
        maxEnergy += reward.value;
    } else if (reward.type == RewardType::MINION_HEALTH) {
        activeBlueprint.healthBonus += reward.value;
    } else if (reward.type == RewardType::MINION_DAMAGE) {
        activeBlueprint.damageBonus += reward.value;
    }
}

void Game::Update() {
    if (WindowShouldClose()) {
        running = false;
    }

    // Energy regeneration
    if (state == GameState::COMBAT || state == GameState::PREPARATION) {
        energyTimer += GetFrameTime();
        float regenRate = 1.0f;
        if (energyTimer >= regenRate) {
            energyTimer -= regenRate;
            if (energy < maxEnergy) {
                energy++;
            }
        }
    }

    // Update effects
    for (auto it = lightningEffects.begin(); it != lightningEffects.end();) {
        it->lifetime -= GetFrameTime();
        if (it->lifetime <= 0) {
            it = lightningEffects.erase(it);
        } else {
            ++it;
        }
    }

    if (state == GameState::PREPARATION) {
        if (IsKeyPressed(KEY_SPACE)) {
            state = GameState::COMBAT;
            enemiesToSpawn = currentWave * 3;
            spawnTimer = spawnDelay;
        }

        // Place crystal
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            int gridX = mousePos.x / TILE_SIZE;
            int gridY = mousePos.y / TILE_SIZE;

            if (map.GetTile(gridX, gridY) == TileType::POWER_NODE) {
                bool hasCrystal = false;
                for (const auto& c : crystals) {
                    if (c->GetPos().x == gridX && c->GetPos().y == gridY) {
                        hasCrystal = true;
                        break;
                    }
                }

                if (!hasCrystal && minerals >= crystalCost) {
                    minerals -= crystalCost;
                    auto c = std::make_unique<Crystal>(Int2{gridX, gridY});
                    c->Init();
                    crystals.push_back(std::move(c));
                }
            }
        }

    } else if (state == GameState::COMBAT) {
        UpdateWaveSpawning();
        HandleHandOfPower();
        HandleMinionSpawning();

        // Combat AI targeting logic
        for (auto& minion : minions) {
            if (!minion->GetTarget() || minion->GetTarget()->IsDead()) {
                minion->SetTarget(nullptr);
                // Find nearest enemy in range
                for (auto& enemy : enemies) {
                    int dist = std::abs(minion->GetPos().x - enemy->GetPos().x) + std::abs(minion->GetPos().y - enemy->GetPos().y);
                    if (dist <= 1) {
                        minion->SetTarget(enemy.get());
                        break;
                    }
                }
            }
        }

        for (auto& enemy : enemies) {
            if (!enemy->GetTarget() || enemy->GetTarget()->IsDead()) {
                enemy->SetTarget(nullptr);
                // Find blocking minion
                for (auto& minion : minions) {
                    int dist = std::abs(enemy->GetPos().x - minion->GetPos().x) + std::abs(enemy->GetPos().y - minion->GetPos().y);
                    if (dist <= 1) {
                        enemy->SetTarget(minion.get());
                        break;
                    }
                }
            }
        }

        for (auto it = enemies.begin(); it != enemies.end();) {
            (*it)->Update();

            if ((*it)->ReachedEye()) {
                eye->TakeDamage(10);
                // Nullify minion targets pointing to this enemy
                for (auto& minion : minions) {
                    if (minion->GetTarget() == it->get()) {
                        minion->SetTarget(nullptr);
                    }
                }
                it = enemies.erase(it);
            } else if ((*it)->IsDead()) {
                minerals += 5;
                ki += 2;
                // Nullify minion targets pointing to this enemy
                for (auto& minion : minions) {
                    if (minion->GetTarget() == it->get()) {
                        minion->SetTarget(nullptr);
                    }
                }
                it = enemies.erase(it);
            } else {
                ++it;
            }
        }

        for (auto it = minions.begin(); it != minions.end();) {
            (*it)->Update();
            if ((*it)->IsDead()) {
                // Nullify enemy targets pointing to this minion
                for (auto& enemy : enemies) {
                    if (enemy->GetTarget() == it->get()) {
                        enemy->SetTarget(nullptr);
                    }
                }
                it = minions.erase(it);
            } else {
                ++it;
            }
        }
        if (eye->GetHealth() <= 0) {
            state = GameState::GAME_OVER;
        }
    } else if (state == GameState::REWARD) {
        int choice = -1;
        if (IsKeyPressed(KEY_ONE)) choice = 0;
        else if (IsKeyPressed(KEY_TWO)) choice = 1;
        else if (IsKeyPressed(KEY_THREE)) choice = 2;

        if (choice != -1) {
            ApplyReward(rewardSystem.GetChoice(choice));
            currentWave++;
            if (currentWave > 5) {
                state = GameState::VICTORY;
            } else {
                state = GameState::PREPARATION;
            }
        }
    }

    if (eye) eye->Update();
    for (auto& c : crystals) c->Update();
}

bool Game::IsInPowerRange(Int2 pos) const {
    int eyeDist = std::abs(pos.x - eye->GetPos().x) + std::abs(pos.y - eye->GetPos().y);
    if (eyeDist <= eye->GetPowerRange()) return true;

    for (const auto& c : crystals) {
        int cDist = std::abs(pos.x - c->GetPos().x) + std::abs(pos.y - c->GetPos().y);
        if (cDist <= c->GetPowerRange()) return true;
    }
    return false;
}

void Game::DrawPowerRanges() {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            if (IsInPowerRange({x, y})) {
                DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, ColorAlpha(PURPLE, 0.2f));
            }
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);

    map.Draw();
    DrawPowerRanges();

    for (auto& c : crystals) c->Draw();
    for (auto& e : enemies) e->Draw();
    for (auto& m : minions) m->Draw();
    if (eye) eye->Draw();

    // Draw effects
    for (const auto& effect : lightningEffects) {
        DrawLineEx({effect.pos.x, effect.pos.y - 100}, effect.pos, 3.0f, YELLOW);
        DrawCircleV(effect.pos, 10.0f * (effect.lifetime / 0.5f), ColorAlpha(YELLOW, effect.lifetime / 0.5f));
    }

    ui.Draw(state, minerals, ki, energy, maxEnergy, currentWave);

    // Draw state specific overlays
    if (state == GameState::COMBAT) {
        DrawText(TextFormat("Spawn Minion: %d Min, %d Ki (Left Click)", activeBlueprint.mineralCost, activeBlueprint.kiCost), 10, 40, 20, WHITE);
    } else if (state == GameState::REWARD) {
        DrawRectangle(0, 0, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, ColorAlpha(BLACK, 0.7f));
        DrawText("REWARD SELECTION", MAP_WIDTH * TILE_SIZE / 2 - MeasureText("REWARD SELECTION", 40) / 2, 100, 40, GOLD);

        for (int i = 0; i < 3; i++) {
            DrawText(TextFormat("%d) %s", i+1, rewardSystem.GetChoice(i).text.c_str()),
                     MAP_WIDTH * TILE_SIZE / 2 - 200, 200 + i * 60, 30, WHITE);
        }
    }

    EndDrawing();
}
