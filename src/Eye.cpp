#include "Eye.h"

Eye::Eye(Int2 pos) : Entity(pos), health(100), maxHealth(100), powerRange(4) {
}

void Eye::Update() {
}

void Eye::Draw() {
    Vector2 wp = GetWorldPos();
    DrawCircle(wp.x + TILE_SIZE/2, wp.y + TILE_SIZE/2, TILE_SIZE/2 - 5, PURPLE);
    DrawCircle(wp.x + TILE_SIZE/2, wp.y + TILE_SIZE/2, TILE_SIZE/4, RED);

    // Draw Health
    DrawRectangle(wp.x, wp.y - 10, TILE_SIZE, 5, RED);
    DrawRectangle(wp.x, wp.y - 10, (float)health/maxHealth * TILE_SIZE, 5, GREEN);
}

void Eye::TakeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}
