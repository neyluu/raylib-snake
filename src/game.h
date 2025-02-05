#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "snake.h"
#include "food.h"

class Game {
private:
    Board board = Board(15, 15, Vector2(30,30), Vector2(0, 0));
    Snake snake;
    Food food;

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
