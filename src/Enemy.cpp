#include "Enemy.h"
#include "Minion.h"
#include <cmath>

Enemy::Enemy(Int2 pos, std::vector<Int2> path)
    : Entity(pos), path(path), pathIndex(0), reachedEye(false), textureLoaded(false), currentTarget(nullptr) {
    health = 20;
    maxHealth = 20;
    damage = 5;
    moveTimer = 0.0f;
    moveDelay = 1.0f; // moves 1 tile per second
    attackTimer = 0.0f;
    attackDelay = 1.0f;
}

Enemy::~Enemy() {
    if (textureLoaded) {
        UnloadTexture(texture);
    }
}

void Enemy::Init() {
    texture = LoadTexture("res/treasure_hunter_lantern_iso_64x64.png");
    textureLoaded = true;
}

void Enemy::Update() {
    if (IsDead() || reachedEye) return;

    if (currentTarget) {
        if (currentTarget->IsDead()) {
            currentTarget = nullptr;
        } else {
            int dist = std::abs(pos.x - currentTarget->GetPos().x) + std::abs(pos.y - currentTarget->GetPos().y);
            if (dist <= 1) {
                attackTimer += GetFrameTime();
                if (attackTimer >= attackDelay) {
                    attackTimer -= attackDelay;
                    currentTarget->TakeDamage(damage);
                }
                return; // Stop moving while attacking
            } else {
                currentTarget = nullptr;
            }
        }
    }

    moveTimer += GetFrameTime();
    if (moveTimer >= moveDelay) {
        moveTimer -= moveDelay;

        if (pathIndex < path.size() - 1) {
            pathIndex++;
            pos = path[pathIndex];
        } else {
            reachedEye = true;
        }
    }
}

void Enemy::Draw() {
    if (IsDead()) return;

    Vector2 wp = GetWorldPos();
    if (textureLoaded) {
        Rectangle dest = { wp.x, wp.y - TILE_SIZE/4, (float)TILE_SIZE, (float)TILE_SIZE };
        Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
        DrawTexturePro(texture, source, dest, {0,0}, 0.0f, WHITE);
    } else {
        DrawCircle(wp.x + TILE_SIZE/2, wp.y + TILE_SIZE/2, TILE_SIZE/3, ORANGE);
    }

    // Health bar
    DrawRectangle(wp.x, wp.y - 5, TILE_SIZE, 4, RED);
    DrawRectangle(wp.x, wp.y - 5, (float)health/maxHealth * TILE_SIZE, 4, GREEN);
}

void Enemy::TakeDamage(int amount) {
    health -= amount;
}
