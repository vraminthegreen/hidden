#pragma once
#include "Types.h"
#include <vector>

enum class TileType {
    EMPTY,
    WALL,
    PATH,
    SPAWN,
    EYE_SPAWN,
    POWER_NODE
};

class Map {
public:
    Map();
    ~Map();

    void Init();
    void Draw();

    TileType GetTile(int x, int y) const;
    void SetTile(int x, int y, TileType type);

    Int2 GetEyePos() const { return eyePos; }
    Int2 GetSpawnPos() const { return spawnPos; }
    std::vector<Int2> GetPowerNodes() const { return powerNodes; }
    std::vector<Int2> GetPath() const { return path; }

private:
    TileType grid[MAP_WIDTH][MAP_HEIGHT];
    Texture2D tileTexture;

    Int2 eyePos;
    Int2 spawnPos;
    std::vector<Int2> powerNodes;
    std::vector<Int2> path;
};
