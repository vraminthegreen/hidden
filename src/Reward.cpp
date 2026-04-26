#include "Reward.h"
#include <cstdlib>

RewardSystem::RewardSystem() {
    GenerateChoices();
}

void RewardSystem::GenerateChoices() {
    for (int i = 0; i < 3; i++) {
        int r = rand() % 4;
        switch(r) {
            case 0:
                choices[i] = {RewardType::RESOURCES, "+50 Minerals & +20 Ki", 50};
                break;
            case 1:
                choices[i] = {RewardType::MAX_ENERGY, "+20 Max Energy", 20};
                break;
            case 2:
                choices[i] = {RewardType::MINION_HEALTH, "+10 Base Minion Health", 10};
                break;
            case 3:
                choices[i] = {RewardType::MINION_DAMAGE, "+5 Base Minion Damage", 5};
                break;
        }
    }
}

Reward RewardSystem::GetChoice(int index) const {
    if (index >= 0 && index < 3) return choices[index];
    return choices[0];
}
