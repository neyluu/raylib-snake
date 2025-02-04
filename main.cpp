#include <iostream>

#include "raylib.h"
#include "src/board.h"

int screenWidth = 800;
int screenHeight = 600;

void UpdateDrawFrame();

Board b(20, 20, Vector2(25, 25), Vector2(50, 50));

int main()
{
    b.setCellBorderColor(Color(40, 40, 40, 255));
    b.centerInWindow(screenWidth, screenHeight);

    InitWindow(screenWidth, screenHeight, "Snake");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }
    CloseWindow();

    return 0;
}

void UpdateDrawFrame()
{
    BeginDrawing();
        ClearBackground(RAYWHITE);

        b.draw();


    EndDrawing();
}