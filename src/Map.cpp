#include "Map.h"

Map::Map() {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            grid[x][y] = TileType::WALL;
        }
    }
    // simple map layout: 1 enemy entrance, 1 main path, chokepoints, 1 eye, 3 nodes
    spawnPos = {0, 7};
    eyePos = {22, 7};

    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 1; y < MAP_HEIGHT-1; y++) {
            grid[x][y] = TileType::EMPTY;
        }
    }

    // Create a path
    for (int x = 0; x <= 22; x++) {
        grid[x][7] = TileType::PATH;
        path.push_back({x, 7});
    }

    grid[0][7] = TileType::SPAWN;
    grid[22][7] = TileType::EYE_SPAWN;

    powerNodes.push_back({8, 4});
    powerNodes.push_back({16, 10});
    powerNodes.push_back({14, 4});

    for (auto node : powerNodes) {
        grid[node.x][node.y] = TileType::POWER_NODE;
    }
}

Map::~Map() {
    if (tileTexture.id != 0) {
        UnloadTexture(tileTexture);
    }
}

void Map::Init() {
    tileTexture = LoadTexture("res/dungeon_tiles.png");
}

void Map::Draw() {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            Rectangle dest = { (float)x * TILE_SIZE, (float)y * TILE_SIZE, (float)TILE_SIZE, (float)TILE_SIZE };
            Rectangle source = { 0, 0, 32, 32 }; // default to some tile

            Color color = WHITE;
            if (grid[x][y] == TileType::WALL) {
                source = { 32, 0, 32, 32 }; // wall tile?
            } else if (grid[x][y] == TileType::PATH) {
                source = { 64, 0, 32, 32 };
                color = LIGHTGRAY;
            } else if (grid[x][y] == TileType::POWER_NODE) {
                source = { 0, 32, 32, 32 };
                color = BLUE;
            } else if (grid[x][y] == TileType::SPAWN) {
                color = RED;
            } else if (grid[x][y] == TileType::EYE_SPAWN) {
                color = PURPLE;
            }

            DrawTexturePro(tileTexture, source, dest, {0,0}, 0.0f, color);
            DrawRectangleLines(dest.x, dest.y, dest.width, dest.height, ColorAlpha(GRAY, 0.2f));
        }
    }
}

TileType Map::GetTile(int x, int y) const {
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) return TileType::WALL;
    return grid[x][y];
}

void Map::SetTile(int x, int y, TileType type) {
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        grid[x][y] = type;
    }
}
