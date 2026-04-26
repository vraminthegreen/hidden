#pragma once
#include <string>
#include <vector>

struct Blueprint {
    std::string id;
    std::string name;

    int healthBonus;
    int damageBonus;
    int mineralCost;
    int kiCost;

    Blueprint() : healthBonus(30), damageBonus(10), mineralCost(10), kiCost(5) {}
};
