#include "game.h"

#include "settings.h"

void Game::init()
{
    board.centerInWindow(settings.screenWidth, settings.screenHeight);
    board.setCellBorderColor(Color(200, 20, 20, 255));

    snake.setBoard(&board);
}


void Game::draw()
{
BeginDrawing();

    ClearBackground(Color(50, 50, 50, 255));
    board.draw();
    snake.draw();

EndDrawing();
}

void Game::update()
{
    snake.update();
}

void Game::run()
{
    if(!isRunning) return;

    update();
    draw();
}