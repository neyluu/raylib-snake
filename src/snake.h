#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "raylib.h"
#include "board.h"
#include "food.h"

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
    Food *food = nullptr;
    bool isAlive = true;
    bool isHungry = true;

    void move();
    void moveUp();
    void moveRight();
    void moveDown();
    void moveLeft();

    void checkCollisions();
    void checkFood();
    bool isHeadInPart(BodyPart part);
    bool isFoodInBody();
public:
    int points = 0;

    void init();
    void draw();
    void update();
    void getEvent();

    void setBoard(Board *board);
    void setFood(Food *food);

    bool alive();
};

#endif //SNAKE_H
