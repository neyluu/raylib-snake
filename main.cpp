#include <iostream>

#include "raylib.h"
#include "src/game.h"
#include "src/settings.h"

int main()
{
    Game game;
    game.init();

    InitWindow(settings.screenWidth, settings.screenHeight, "Snake");
//    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if(!game.run()) break;
    }
    CloseWindow();

    return 0;
}