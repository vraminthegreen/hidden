#include "Crystal.h"

Crystal::Crystal(Int2 pos) : Entity(pos), powerRange(3), textureLoaded(false) {
}

Crystal::~Crystal() {
    if (textureLoaded) {
        UnloadTexture(texture);
    }
}

void Crystal::Init() {
    texture = LoadTexture("res/power_crystal_iso_128x128.png");
    textureLoaded = true;
}

void Crystal::Update() {
}

void Crystal::Draw() {
    Vector2 wp = GetWorldPos();
    if (textureLoaded) {
        // adjust scale based on tile size
        Rectangle dest = { wp.x, wp.y - TILE_SIZE/2, (float)TILE_SIZE, (float)TILE_SIZE * 2 };
        Rectangle source = { 0, 0, (float)texture.width, (float)texture.height };
        DrawTexturePro(texture, source, dest, {0,0}, 0.0f, WHITE);
    } else {
        DrawRectangle(wp.x + 10, wp.y + 10, TILE_SIZE - 20, TILE_SIZE - 20, BLUE);
    }
}
