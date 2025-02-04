#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "raylib.h"
#include "board.h"

enum Direction
{
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};

typedef struct
{
    Vector2 position;
} BodyPart;

class Snake {
private:
    Direction direction = RIGHT;
    std::vector<BodyPart> body;
    Board *board = nullptr;
public:

    void draw();
    void update();

    void setBoard(Board *board);
};

#endif //SNAKE_H
