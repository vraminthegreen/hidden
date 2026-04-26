#pragma once
#include "Entity.h"
#include "Blueprint.h"

class Enemy; // forward declaration

class Minion : public Entity {
public:
    Minion(Int2 pos, const Blueprint& bp);
    ~Minion() override;

    void Init();
    void Update() override;
    void Draw() override;

    // For combat interaction
    void SetTarget(Enemy* target) { currentTarget = target; }
    Enemy* GetTarget() const { return currentTarget; }

    bool IsDead() const { return health <= 0; }
    int GetHealth() const { return health; }
    int GetDamage() const { return damage; }
    void TakeDamage(int amount);

private:
    Blueprint blueprint;
    int health;
    int maxHealth;
    int damage;

    float attackTimer;
    float attackDelay;

    Enemy* currentTarget;

    Texture2D texture;
    bool textureLoaded;
};
