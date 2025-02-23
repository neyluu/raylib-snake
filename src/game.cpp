#include "game.h"

#include "settings.h"

Game::~Game()
{
    for(Level *level : levels)
    {
        delete level;
    }
}

void Game::init()
{
    srand(time(NULL));

    createLevels();

    gui.addButton(Button(Rectangle(0, settings.screenHeight - 60, 150, 60), RED, "RESET", &events.Game_reset));
    gui.addButton(Button(Rectangle(160, settings.screenHeight - 60, 150, 60), GREEN, "PAUSE", &events.Game_pause));

    gui.addPopup( "GAME_OVER",
      Popup(Rectangle(settings.screenWidth / 2 - 150, settings.screenHeight / 2 - 75, 300, 150), Color(255, 255, 255, 25), "GAME OVER", 30, BLACK));
    gui.addPopup("PAUSE",
                 Popup(Rectangle(settings.screenWidth / 2 - 125, settings.screenHeight / 2 - 20, 250, 40), Color(255, 255, 255, 100), "GAME IS PAUSED", 30, BLACK));
}

void Game::createLevels()
{
    StandardLevel *lvl = new StandardLevel(&tickRate);
    {
        lvl->setBoardSize(6, 6);
        lvl->setBorderColor(BLACK);
        lvl->setCellBackgroundColor(DARKBROWN);
        lvl->setCellSize(80, 80);
        lvl->setBoardBorderSize(13);
        lvl->centerBoard();

        lvl->setFoodColor(Color(230, 40, 40, 255));
        lvl->setFoodSize(25);

        lvl->setSnakeStartSize(3);
        lvl->setSnakeStartingPosition(2, 0);
        lvl->setSnakeStartingDirection(RIGHT);
        lvl->setSnakeHeadColor(GOLD);
        lvl->setSnakeBodyColor(MAGENTA);

        lvl->setLevelSpeed(0.75);
    }
    levels.push_back(lvl);

    StandardLevel *lvl2 = new StandardLevel(&tickRate);
    {
        lvl2->setBoardSize(12, 12);
        lvl2->setBorderColor(BLUE);
        lvl2->setCellBackgroundColor(LIGHTGRAY);
        lvl2->setCellSize(32, 32);
        lvl2->setBoardBorderSize(5);
        lvl2->centerBoard();

        lvl2->setFoodColor(Color(40, 250, 40, 255));
        lvl2->setFoodSize(10);

        lvl2->setSnakeStartSize(4);
        lvl2->setSnakeStartingPosition(4, 4);
        lvl2->setSnakeStartingDirection(LEFT);
        lvl2->setSnakeHeadColor(GREEN);
        lvl2->setSnakeBodyColor(ORANGE);

        lvl2->setLevelSpeed(2);
    }
    levels.push_back(lvl2);

    ptrCurrentLevel = lvl;

}

void Game::draw()
{
BeginDrawing();
    DrawFPS(5, 5);
    ClearBackground(Color(50, 50, 50, 255));

    ptrCurrentLevel->draw();

    gui.drawScore(ptrCurrentLevel->getPoints());
    gui.drawHighScore(ptrCurrentLevel->getHighScore());
    gui.draw();
    if(!ptrCurrentLevel->isSnakeAlive()) gui.setPopupVisibility("GAME_OVER", true);

EndDrawing();
}

void Game::update()
{
    if(!isPaused) ptrCurrentLevel->update();
}

void Game::getEvents()
{
    if(IsKeyPressed(settings.keymap.exitGame)) isRunning = false;

    ptrCurrentLevel->getEvents();
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

    ptrCurrentLevel->reset();
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

    if(simulationTime >= tickRate * ptrCurrentLevel->getLevelSpeed())
    {
        simulationTime -= tickRate * ptrCurrentLevel->getLevelSpeed();
        update();
    }

    draw();
    return true;
}

void Game::pause()
{
    isPaused = !isPaused;
    ptrCurrentLevel->togglePause();
    if(isPaused && ptrCurrentLevel->isSnakeAlive()) gui.setPopupVisibility("PAUSE", true);
    if(!isPaused) gui.setPopupVisibility("PAUSE", false);
}