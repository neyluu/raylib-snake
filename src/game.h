#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>

#include "board.h"
#include "snake.h"
#include "food.h"
#include "gui/gui.h"
#include "gui/events.h"
#include "levels/levels.h"

class Game {
private:
    Board board = Board(15, 15, Vector2(30,30), Vector2(0, 0));
    Snake snake = Snake(3, 28, 28, DARKBLUE, WHITE);
    Food food;
    Gui gui;
    Events events;

    std::vector<Level*> levels;

    double tickRate = 1.0 / 5.0;
    bool isPaused = false;

    void draw();
    void update();

public:
    bool isRunning = true;

    bool run();
    void init();
    void getEvents();
    void checkButtonEvents();
    void reset();
    void pause();
};

#endif //GAME_H
