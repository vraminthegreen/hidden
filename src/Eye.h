#pragma once
#include "Entity.h"

class Eye : public Entity {
public:
    Eye(Int2 pos);
    ~Eye() override = default;

    void Update() override;
    void Draw() override;

    int GetPowerRange() const { return powerRange; }
    int GetHealth() const { return health; }
    int GetMaxHealth() const { return maxHealth; }
    void TakeDamage(int amount);

private:
    int health;
    int maxHealth;
    int powerRange;
};
