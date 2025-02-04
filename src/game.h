#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "snake.h"

class Game {
private:
    Board board = Board(15, 15, Vector2(30,30), Vector2(0, 0));
    Snake snake;

    void draw();
    void update();
public:
    bool isRunning = true;

    void init();
    void run();
};


#endif //GAME_H
