#include "game.h"

#include "settings.h"

void Game::init()
{
    srand(time(NULL));

    board.centerInWindow(settings.screenWidth, settings.screenHeight);
    board.setCellBorderColor(Color(200, 20, 20, 255));

    food.setBoard(&board);
    food.init();

    snake.setBoard(&board);
    snake.setFood(&food);
    snake.init();
}

void Game::draw()
{
BeginDrawing();
    DrawFPS(5, 5);

    ClearBackground(Color(50, 50, 50, 255));
    board.draw();
    food.draw();
    snake.draw();
    gui.drawScore(snake.points);

    if(!snake.alive()) gui.drawGameOver();

EndDrawing();
}

void Game::update()
{
    snake.update();
}

void Game::getEvents()
{
    snake.getEvent();
}

void Game::run()
{
    if(!isRunning) return;

    getEvents();

    static bool timeOnce = false;
    static double t0 = 0.0;
    static double simulationTime = 0.0;

    if(!timeOnce)
    {
        t0 = GetTime();
        timeOnce = true;
    }

    double t1 = GetTime();
    double elapsed = t1 - t0;
    if(elapsed > 0.25) elapsed = 0.25;

    t0 = t1;
    simulationTime += elapsed;

    if(simulationTime >= tickRate)
    {
        simulationTime -= tickRate;
        update();
    }

    draw();
}