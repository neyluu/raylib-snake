#ifndef GAME_H
#define GAME_H

#include "board.h"

class Settings {
private:
public:
};

class Game {
private:
    Board board;
public:
    void draw();
    void update();
};


#endif //GAME_H
