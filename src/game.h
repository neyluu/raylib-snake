#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>

#include "board.h"
#include "snake.h"
#include "food.h"
#include "gui/gui.h"
#include "gui/events.h"

class Game {
private:
    Board board = Board(15, 15, Vector2(30,30), Vector2(0, 0));
    Snake snake;
    Food food;
    Gui gui;
    Events events;

    double tickRate = 1.0 / 5.0;
    bool isPaused = false;

    void draw();
    void update();

public:
    bool isRunning = true;

    bool run();
    void init();
    void getEvents();
    void checkEvents();
    void reset();
    void pause();
};

#endif //GAME_H
