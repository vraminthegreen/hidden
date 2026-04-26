#include "UI.h"
#include <raylib.h>
#include "Reward.h"

void UI::Init() {
}

void UI::DrawTextCentered(const char* text, int y, int fontSize, Color color) {
    int width = MeasureText(text, fontSize);
    DrawText(text, (MAP_WIDTH * TILE_SIZE - width) / 2, y, fontSize, color);
}

void UI::Draw(GameState state, int minerals, int ki, int energy, int maxEnergy, int wave) {
    // Draw top bar
    DrawRectangle(0, 0, MAP_WIDTH * TILE_SIZE, 40, ColorAlpha(BLACK, 0.8f));

    std::string resources = "Minerals: " + std::to_string(minerals) +
                          " | Ki: " + std::to_string(ki) +
                          " | Energy: " + std::to_string(energy) + "/" + std::to_string(maxEnergy) +
                          " | Wave: " + std::to_string(wave);

    DrawText(resources.c_str(), 10, 10, 20, WHITE);

    // Draw state specific UI
    if (state == GameState::PREPARATION) {
        DrawTextCentered("PREPARATION PHASE - Press SPACE to start wave", 50, 20, YELLOW);
    } else if (state == GameState::COMBAT) {
        DrawTextCentered("COMBAT PHASE", 50, 20, RED);
    } else if (state == GameState::GAME_OVER) {
        DrawRectangle(0, 0, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, ColorAlpha(RED, 0.3f));
        DrawTextCentered("GAME OVER", MAP_HEIGHT * TILE_SIZE / 2 - 40, 60, MAROON);
        DrawTextCentered("The Eye has been destroyed.", MAP_HEIGHT * TILE_SIZE / 2 + 40, 20, WHITE);
    } else if (state == GameState::VICTORY) {
        DrawRectangle(0, 0, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, ColorAlpha(GREEN, 0.3f));
        DrawTextCentered("VICTORY!", MAP_HEIGHT * TILE_SIZE / 2 - 40, 60, GOLD);
        DrawTextCentered("You have defended the dungeon.", MAP_HEIGHT * TILE_SIZE / 2 + 40, 20, WHITE);
    }
}
