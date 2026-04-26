#include "Game.h"
#include <raylib.h>

int main() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "Evil Eye");
    SetTargetFPS(60);

    {
    Game game;
    game.Init();

    while (game.IsRunning()) {
        game.Update();
        game.Draw();
    }

    }
    CloseWindow();
    return 0;
}
