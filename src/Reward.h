#pragma once
#include <string>

enum class RewardType {
    RESOURCES,
    MAX_ENERGY,
    MINION_HEALTH,
    MINION_DAMAGE
};

struct Reward {
    RewardType type;
    std::string text;
    int value;
};

class RewardSystem {
public:
    RewardSystem();
    void GenerateChoices();
    Reward GetChoice(int index) const;

private:
    Reward choices[3];
};
