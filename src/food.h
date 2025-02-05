#ifndef FOOD_H
#define FOOD_H

#include "board.h"

class Food {
private:
    float radius = 0.0;
    Color color = RED;
    Vector2 position = {0, 0};
    Board *board = nullptr;
public:
    void init();
    void draw();
    void setBoard(Board *board);
};

#endif //FOOD_H
