#pragma once

#include <raylib.h>

const int TILE_SIZE = 64;
const int MAP_WIDTH = 24;
const int MAP_HEIGHT = 14;

enum class GameState {
    PREPARATION,
    COMBAT,
    REWARD,
    GAME_OVER,
    VICTORY
};

struct Int2 {
    int x;
    int y;

    bool operator==(const Int2& other) const {
        return x == other.x && y == other.y;
    }
};
