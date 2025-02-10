#include "game.h"

#include "settings.h"

void Game::init()
{
    srand(time(NULL));

    gui.addButton(Button(Rectangle(0, settings.screenHeight - 100, 150, 100), RED, "RESET", &events.Game_reset));
    gui.addButton(Button(Rectangle(160, settings.screenHeight - 100, 150, 100), GREEN, "PAUSE", &events.Game_pause));

    gui.addPopup( "GAME_OVER",
      Popup(Rectangle(settings.screenWidth / 2 - 150, settings.screenHeight / 2 - 75, 300, 150), WHITE, "GAME OVER", 30, BLACK));
    gui.addPopup("PAUSE",
                 Popup(Rectangle(settings.screenWidth / 2 - 150, settings.screenHeight / 2 - 75, 300, 150), WHITE, "GAME IS PAUSED", 30, BLACK));

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
    gui.draw();
//    if(!snake.alive()) gui.drawGameOver();
    if(!snake.alive()) gui.setPopupVisibility("GAME_OVER", true);
    if(isPaused && snake.alive()) gui.setPopupVisibility("PAUSE", true);
    if(!isPaused) gui.setPopupVisibility("PAUSE", false);

EndDrawing();
}

void Game::update()
{
    if(!isPaused) snake.update();
}

void Game::getEvents()
{
    snake.getEvent();
    gui.getEvents();
}

void Game::checkEvents()
{
    if(events.Game_reset) reset();
    if(events.Game_pause) pause();

    events.setDefault();
}

void Game::reset()
{
    // TODO implementation
    std::cout << "RESETING GAME" << std::endl;

    snake.reset();
    gui.setPopupVisibility("GAME_OVER", false);
}

void Game::run()
{
    if(!isRunning) return;

    getEvents();
    checkEvents();

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

void Game::pause()
{
    isPaused = !isPaused;
}