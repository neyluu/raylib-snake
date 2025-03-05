#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "raylib.h"
#include "board.h"
#include "food/foodContainer.h"
#include "settings.h"
#include "direction.h"
#include "utils.h"

struct BodyPart
{
    Vector2 position;
    Direction direction;

    BodyPart() = default;
    BodyPart(Vector2 position, Direction direction);
};

class Snake
{
public:
    int points = 0;
    int highScore = 0;
    bool isPaused = false;

    Snake(Board *board, FoodContainer *foods);
    Snake(Board *board, FoodContainer *foods, int startSize, int bodyPartWidth, int bodyPartHeight, Color headColor, Color bodyColor);

    bool alive() const;

    void setStartSize(int size);
    void setBodyPartSize(int width, int height);
    void setStartingPosition(Vector2 position);
    void setStartingDirection(Direction direction);
    void setHeadColor(Color color);
    void setBodyColor(Color color);

    void init();
    void draw(double tickRate);
    void update();
    void getEvent();
    void reset();
private:
    Direction startingDirection = RIGHT;
    Direction direction = startingDirection;
    Direction newDirection = startingDirection;
    std::vector<BodyPart> body;
    FoodContainer *foods = nullptr;
    bool isAlive = true;
    bool isHungry = true;
    bool tailAnim = true;

    float totalAnimationStep = 0;

    int startSize = 3;
    int bodyPartWidth = 20;
    int bodyPartHeight = 20;
    Color headColor = GREEN;
    Color bodyColor = SKYBLUE;
    Vector2 startingPosition = { 0, 0 };

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
    bool isFoodInBody(Food *food);

    bool isPartLeftUpCorner(int i);
    bool isPartRightUpCorner(int i);
    bool isPartLeftBottomCorner(int i);
    bool isPartRightBottomCorner(int i);
    bool isPartVertical(int i);
    bool isPartHorizontal(int i);
    bool isPartPenultimate(int i);
};

#endif
