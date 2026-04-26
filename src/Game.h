#pragma once
#include "Types.h"
#include "Map.h"
#include "UI.h"
#include "Eye.h"
#include "Crystal.h"
#include "Enemy.h"
#include "Input.h"
#include "Minion.h"
#include "Blueprint.h"
#include "Reward.h"
#include <vector>
#include <memory>

class Game {
public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Draw();

    bool IsRunning() const { return running; }
    void Close() { running = false; }

private:
    void DrawPowerRanges();
    bool IsInPowerRange(Int2 pos) const;
    void UpdateWaveSpawning();
    void HandleHandOfPower();
    void HandleMinionSpawning();
    void ApplyReward(const Reward& reward);

    bool running;
    GameState state;
    Map map;
    UI ui;
    RewardSystem rewardSystem;

    std::unique_ptr<Eye> eye;
    std::vector<std::unique_ptr<Crystal>> crystals;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Minion>> minions;

    Blueprint activeBlueprint;

    int minerals;
    int ki;
    int energy;
    int maxEnergy;
    int currentWave;

    int crystalCost = 20;
    int lightningCost = 15;
    int lightningDamage = 10;
    float energyTimer = 0.0f;

    // Wave data
    int enemiesToSpawn;
    float spawnTimer;
    float spawnDelay;

    // Visual effects
    struct LightningEffect {
        Vector2 pos;
        float lifetime;
    };
    std::vector<LightningEffect> lightningEffects;
};
