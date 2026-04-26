#pragma once
#include "Types.h"
#include <raylib.h>

class Entity {
public:
    Entity(Int2 pos);
    virtual ~Entity() = default;

    virtual void Update() = 0;
    virtual void Draw() = 0;

    Int2 GetPos() const { return pos; }
    Vector2 GetWorldPos() const { return { (float)pos.x * TILE_SIZE, (float)pos.y * TILE_SIZE }; }

protected:
    Int2 pos;
};
