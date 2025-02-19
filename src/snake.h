#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "raylib.h"
#include "board.h"
#include "food.h"
#include "settings.h"
#include "direction.h"

struct BodyPart
{
    Vector2 position;
    Direction direction;

    BodyPart() = default;
    BodyPart(Vector2 position, Direction direction);
};

class Snake {
private:
    Direction direction = RIGHT;
    Direction newDirection = RIGHT;
    std::vector<BodyPart> body;
    Board *board = nullptr;
    Food *food = nullptr;
    bool isAlive = true;
    bool isHungry = true;

    float totalAnimationStep = 0;

    int startSize = 1;
    int bodyPartWidth = 28;
    int bodyPartHeight = 28;
    Color headColor = GREEN;
    Color bodyColor = SKYBLUE;

    void move();
    void moveUp();
    void moveRight();
    void moveDown();
    void moveLeft();

    void checkCollisions();
    void checkFood();

    void drawHead();
    void drawTail();

    bool isHeadInPart(BodyPart part);
    bool isFoodInBody();

    bool isPartLeftUpCorner(int i);
    bool isPartRightUpCorner(int i);
    bool isPartLeftBottomCorner(int i);
    bool isPartRightBottomCorner(int i);
    bool isPartVertical(int i);
    bool isPartHorizontal(int i);
public:
    int points = 0;
    int highScore = 0;
    bool isPaused = false;

    Snake() {};
    Snake(int startSize, int bodyPartWidth, int bodyPartHeight, Color headColor, Color bodyColor);

    void init();
    void draw(double tickRate);
    void update();
    void getEvent();
    void reset();

    void setBoard(Board *board);
    void setFood(Food *food);

    bool alive();
};

#endif //SNAKE_H
