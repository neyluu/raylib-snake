#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>

#include "board.h"
#include "snake.h"
#include "food.h"
#include "gui/gui.h"

class Game {
private:
    Board board = Board(15, 15, Vector2(30,30), Vector2(0, 0));
    Snake snake;
    Food food;
    Gui gui;

    double tickRate = 1.0 / 5.0;

    void draw();
    void update();
public:
    bool isRunning = true;

    void init();
    void run();
    void getEvents();
};


#endif //GAME_H
