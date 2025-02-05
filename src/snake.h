#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "raylib.h"
#include "board.h"

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct BodyPart
{
    Vector2 position;

    BodyPart() = default;
    BodyPart(Vector2 position);
};

class Snake {
private:
    Direction direction = RIGHT;
    std::vector<BodyPart> body;
    Board *board = nullptr;
    bool isAlive = true;

    void move();
    void moveUp();
    void moveRight();
    void moveDown();
    void moveLeft();

    void checkCollisions();
public:
    void init();
    void draw();
    void update();
    void getEvent();

    void setBoard(Board *board);
};

#endif //SNAKE_H
