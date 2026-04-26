#include "Minion.h"
#include "Enemy.h"
#include <cmath>

Minion::Minion(Int2 pos, const Blueprint& bp)
    : Entity(pos), blueprint(bp), currentTarget(nullptr), textureLoaded(false) {
    maxHealth = bp.healthBonus;
    health = maxHealth;
    damage = bp.damageBonus;

    attackTimer = 0.0f;
    attackDelay = 1.0f; // 1 attack per second
}

Minion::~Minion() {
    if (textureLoaded) {
        UnloadTexture(texture);
    }
}

void Minion::Init() {
    texture = LoadTexture("res/skeleton_sword_iso_64x64.png");
    textureLoaded = true;
}

void Minion::Update() {
    if (IsDead()) return;

    if (currentTarget) {
        if (currentTarget->IsDead()) {
            currentTarget = nullptr;
        } else {
            // Check distance
            int dist = std::abs(pos.x - currentTarget->GetPos().x) + std::abs(pos.y - currentTarget->GetPos().y);
            if (dist <= 1) {
                attackTimer += GetFrameTime();
                if (attackTimer >= attackDelay) {
                    attackTimer -= attackDelay;
                    currentTarget->TakeDamage(damage);
                }
            } else {
                currentTarget = nullptr;
                attackTimer = 0.0f;
            }
        }
    }
}

void Minion::Draw() {
    if (IsDead()) return;

    Vector2 wp = GetWorldPos();
    if (textureLoaded) {
        Rectangle dest = { wp.x, wp.y - TILE_SIZE/4, (float)TILE_SIZE, (float)TILE_SIZE };
        Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
        DrawTexturePro(texture, source, dest, {0,0}, 0.0f, WHITE);
    } else {
        DrawCircle(wp.x + TILE_SIZE/2, wp.y + TILE_SIZE/2, TILE_SIZE/3, LIGHTGRAY);
    }

    // Health bar
    DrawRectangle(wp.x, wp.y - 5, TILE_SIZE, 4, RED);
    DrawRectangle(wp.x, wp.y - 5, (float)health/maxHealth * TILE_SIZE, 4, GREEN);
}

void Minion::TakeDamage(int amount) {
    health -= amount;
}
