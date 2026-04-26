#pragma once
#include "Types.h"
#include <string>

class UI {
public:
    void Init();
    void Draw(GameState state, int minerals, int ki, int energy, int maxEnergy, int wave);

private:
    void DrawTextCentered(const char* text, int y, int fontSize, Color color);
};
