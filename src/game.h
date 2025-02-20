#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>

#include "gui/gui.h"
#include "gui/events.h"
#include "levels/levels.h"

class Game {
private:
    Gui gui;
    Events events;

    std::vector<Level*> levels;
    Level *ptrCurrentLevel = nullptr;

    double tickRate = 1.0 / 5.0;
    bool isPaused = false;

    unsigned int currentLevel = 0;

    void draw();
    void update();

public:
    bool isRunning = true;

    ~Game();

    bool run();
    void init();
    void getEvents();
    void checkButtonEvents();
    void reset();
    void pause();
};

#endif //GAME_H
