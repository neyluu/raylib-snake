#include "game.h"

#include "settings.h"

void Game::init()
{
// ===================
    StandardLevel stdLvl1 = StandardLevel(3);
    StandardLevel stdLvl2= StandardLevel(4);

    levels.push_back(&stdLvl1);
    levels.push_back(&stdLvl2);

    for(Level *level : levels)
    {
        level->test();
    }
// ===================


    srand(time(NULL));

    gui.addButton(Button(Rectangle(0, settings.screenHeight - 60, 150, 60), RED, "RESET", &events.Game_reset));
    gui.addButton(Button(Rectangle(160, settings.screenHeight - 60, 150, 60), GREEN, "PAUSE", &events.Game_pause));

    gui.addPopup( "GAME_OVER",
      Popup(Rectangle(settings.screenWidth / 2 - 150, settings.screenHeight / 2 - 75, 300, 150), WHITE, "GAME OVER", 30, BLACK));
    gui.addPopup("PAUSE",
                 Popup(Rectangle(settings.screenWidth / 2 - 125, settings.screenHeight / 2 - 20, 250, 40), Color(255, 255, 255, 100), "GAME IS PAUSED", 30, BLACK));

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
    snake.draw(tickRate);

    gui.drawScore(snake.points);
    gui.drawHighScore(snake.highScore);
    gui.draw();
    if(!snake.alive()) gui.setPopupVisibility("GAME_OVER", true);

EndDrawing();
}

void Game::update()
{
    if(!isPaused) snake.update();
}

void Game::getEvents()
{
    if(IsKeyPressed(settings.keymap.exitGame)) isRunning = false;

    snake.getEvent();
    gui.getEvents();
}

void Game::checkButtonEvents()
{
    if(events.Game_reset || IsKeyPressed(settings.keymap.resetGame)) reset();
    if(events.Game_pause || IsKeyPressed(settings.keymap.pauseGame)) pause();

    events.setDefault();
}

void Game::reset()
{
    // TODO implementation
    std::cout << "RESETING GAME" << std::endl;

    snake.reset();
    gui.setPopupVisibility("GAME_OVER", false);
    isPaused = false;
}

bool Game::run()
{
    if(!isRunning) return false;

    getEvents();
    checkButtonEvents();

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
    return true;
}

void Game::pause()
{
    isPaused = !isPaused;
    snake.isPaused = !snake.isPaused;
    if(isPaused && snake.alive()) gui.setPopupVisibility("PAUSE", true);
    if(!isPaused) gui.setPopupVisibility("PAUSE", false);
}