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
    srand(time(nullptr));

    createLevels();

    gui.addButton("RESET", Button(Rectangle(0, settings.screenHeight - 60, 150, 60), RED, "RESET"));
    gui.addButton("PAUSE", Button(Rectangle(160, settings.screenHeight - 60, 150, 60), GREEN, "PAUSE"));
    gui.addButton("NEXT_LEVEL", Button(Rectangle(320, settings.screenHeight - 60, 220, 60), YELLOW, "NEXT LEVEL"));
    gui.setButtonVisibility("NEXT_LEVEL", false);

    gui.addPopup( "GAME_OVER",
      Popup(Rectangle(settings.screenWidth / 2 - 150, settings.screenHeight / 2 - 75, 300, 150), Color(255, 255, 255, 25), "GAME OVER", 30, BLACK));
    gui.addPopup("PAUSE",
                 Popup(Rectangle(settings.screenWidth / 2 - 125, settings.screenHeight / 2 - 20, 250, 40), Color(255, 255, 255, 100), "GAME IS PAUSED", 30, BLACK));
    gui.addPopup("WIN",
                 Popup(Rectangle(settings.screenWidth / 2 - 125, settings.screenHeight / 2 - 20, 250, 40), WHITE, "YOU WIN", 30, BLACK));
}

void Game::createLevels()
{
    StandardLevel *lvl1 = new StandardLevel(&tickRate);
    {
        lvl1->setBoardSize(15, 15);
        lvl1->setBorderColor(BLACK);
        lvl1->setBoardCellBackgroundColor(DARKBROWN);
        lvl1->setBoardCellSize(32, 32);
        lvl1->setBoardBorderSize(4);
        lvl1->centerBoard();
        lvl1->setFoodColor(Color(230, 0, 40, 100));
        lvl1->setFoodSize(10);
        lvl1->setFoodCount(1);
        lvl1->setSnakeStartSize(3);
        lvl1->setSnakeStartingPosition(2, 0);
        lvl1->setSnakeStartingDirection(RIGHT);
        lvl1->setSnakeHeadColor(GOLD);
        lvl1->setSnakeBodyColor(MAGENTA);
        lvl1->setLevelSpeed(0.75);
        lvl1->pointsTarget = 100;
    }
    levels.push_back(lvl1);

    StandardLevel *lvl2 = new StandardLevel(&tickRate);
    {
        lvl2->setBoardSize(12, 12);
        lvl2->setBorderColor({40, 40, 40, 255});
        lvl2->setBoardCellBackgroundColor(BLACK);
        lvl2->setBoardCellSize(40, 40);
        lvl2->setBoardBorderSize(5);
        lvl2->centerBoard();

        lvl2->setFoodColor(Color(220, 30, 40, 255));
        lvl2->setFoodSize(10);

        lvl2->setSnakeStartSize(4);
        lvl2->setSnakeStartingPosition(4, 4);
        lvl2->setSnakeStartingDirection(LEFT);
        lvl2->setSnakeHeadColor(GREEN);
        lvl2->setSnakeBodyColor(ORANGE);

        lvl2->setLevelSpeed(1);

        lvl2->pointsTarget = 5;
    }
    levels.push_back(lvl2);

    StandardLevel *lvl3 = new StandardLevel(&tickRate);
    {
        lvl3->setBoardSize(9, 9);
        lvl3->setBorderColor(RED);
        lvl3->setBoardCellBackgroundColor(BLUE);
        lvl3->setBoardCellSize(50, 50);
        lvl3->setBoardBorderSize(4);
        lvl3->centerBoard();

        lvl3->setFoodColor(GREEN);
        lvl3->setFoodSize(20);

        lvl3->setSnakeStartSize(3);
        lvl3->setSnakeStartingPosition(1, 3);
        lvl3->setSnakeStartingDirection(DOWN);
        lvl3->setSnakeHeadColor(BLACK);
        lvl3->setSnakeBodyColor(WHITE);

        lvl3->setLevelSpeed(1.25);

        lvl3->pointsTarget = 1;
    }
    levels.push_back(lvl3);

//    currentLevel = 3;
    ptrCurrentLevel = lvl1;
}
void Game::nextLevel()
{
    pause();
    currentLevel++;
    ptrCurrentLevel = levels[currentLevel];
    gui.setPopupVisibility("WIN", false);
    gui.setButtonVisibility("NEXT_LEVEL", false);
}

void Game::handleWin()
{
    if(!isPaused)
    {
        isPaused = !isPaused;
        ptrCurrentLevel->togglePause();
        gui.setPopupVisibility("WIN", true);
    }
    if(currentLevel + 1 < levels.size())
    {
        gui.setButtonVisibility("NEXT_LEVEL", true);
    }
    else
    {
        std::cout << "No more levels!" << std::endl;
    }
}

void Game::draw()
{
BeginDrawing();

    DrawFPS(5, 5);
    ClearBackground(Color(50, 50, 50, 255));

    ptrCurrentLevel->draw();

    gui.drawCounter(15, 35, "SCORE: ", ptrCurrentLevel->getPoints());
    gui.drawCounter(15, 80, "HIGHSCORE: ", ptrCurrentLevel->getHighScore());
    gui.drawCounter(15, 125, "FOOD LEFT: ", ptrCurrentLevel->getPointsTarget() - ptrCurrentLevel->getPoints());
    gui.drawCounter(15, 170, "LEVEL: ", currentLevel + 1);

    gui.draw();
    if(!ptrCurrentLevel->isSnakeAlive()) gui.setPopupVisibility("GAME_OVER", true);

EndDrawing();
}

void Game::update()
{
    if(!isPaused) ptrCurrentLevel->update();
    if(ptrCurrentLevel->isWin()) handleWin();
}

void Game::getEvents()
{
    if(IsKeyPressed(settings.keymap.exitGame)) isRunning = false;

    ptrCurrentLevel->getEvents();
//    gui.getEvents();
}
void Game::checkButtonEvents()
{
    if(!ptrCurrentLevel->isWin() && (gui.isButtonClicked("RESET") || IsKeyPressed(settings.keymap.resetGame))) reset();
    if(!ptrCurrentLevel->isWin() && (gui.isButtonClicked("PAUSE") || IsKeyPressed(settings.keymap.pauseGame))) pause();
    if(ptrCurrentLevel->isWin() && (gui.isButtonClicked("NEXT_LEVEL") || IsKeyPressed(settings.keymap.nextLevel))) nextLevel();
}

void Game::reset()
{
    // TODO implementation
    std::cout << "RESETING GAME" << std::endl;

    ptrCurrentLevel->reset();
    gui.setPopupVisibility("GAME_OVER", false);
    gui.setPopupVisibility("PAUSE", false);
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