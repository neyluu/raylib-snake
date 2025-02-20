#ifndef RAYLIB_SNAKE_STANDARDLEVEL_H
#define RAYLIB_SNAKE_STANDARDLEVEL_H

#include "level.h"

#include "../board.h"
#include "../snake.h"
#include "../food.h"

class StandardLevel : public Level
{
private:
    Board board = Board(15, 15, Vector2(30,30), Vector2(0, 0));
    Snake snake = Snake(3, 28, 28, DARKBLUE, WHITE);
    Food food;

    float levelSpeed = 1;
    const double * tickRate = nullptr;
public:
    StandardLevel(double *tickRate);
    ~StandardLevel() override { }

    void draw() override;
    void update() override;
    void reset() override;
    void getEvents() override;

    int getPoints()     override { return snake.points; }
    int getHighScore()  override { return snake.highScore; }
    bool isSnakeAlive() override { return snake.alive(); }
    void togglePause()  override { snake.isPaused = !snake.isPaused; }
};


#endif
