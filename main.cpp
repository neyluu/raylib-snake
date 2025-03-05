#include <iostream>

#include "raylib.h"
#include "src/game.h"
#include "src/settings.h"

int main()
{
    InitWindow(settings.screenWidth, settings.screenHeight, "Snake");

    Game game;
    game.init();

//    SetTargetFPS(300);

    while (!WindowShouldClose())
    {
        if(!game.run()) break;
    }
    CloseWindow();

    return 0;
}