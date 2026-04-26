#pragma once
#include "Entity.h"
#include <vector>

class Minion; // forward decl

class Enemy : public Entity {
public:
    Enemy(Int2 pos, std::vector<Int2> path);
    ~Enemy() override;

    void Init();
    void Update() override;
    void Draw() override;

    void SetTarget(Minion* target) { currentTarget = target; }
    Minion* GetTarget() const { return currentTarget; }

    bool IsDead() const { return health <= 0; }
    bool ReachedEye() const { return reachedEye; }
    int GetHealth() const { return health; }
    void TakeDamage(int amount);

private:
    int health;
    int maxHealth;
    float moveTimer;
    float moveDelay;
    int damage;

    float attackTimer;
    float attackDelay;

    Minion* currentTarget;

    std::vector<Int2> path;
    int pathIndex;
    bool reachedEye;

    Texture2D texture;
    bool textureLoaded;
};
