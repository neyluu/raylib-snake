#ifndef RAYLIB_SNAKE_STANDARDLEVEL_H
#define RAYLIB_SNAKE_STANDARDLEVEL_H

#include <vector>

#include "level.h"

#include "../board.h"
#include "../snake.h"
#include "../food/foodContainer.h"

class StandardLevel : public Level
{
private:
    Board *board = new Board();
    FoodContainer *foods = new FoodContainer(board);
    Snake *snake = new Snake(board, foods);

    float levelSpeed = 1 / 1;
    const double * tickRate = nullptr;

public:
    bool win = false;
    int pointsTarget = 1;

    StandardLevel(double *tickRate);
    ~StandardLevel() override;

    void init() override;
    void draw() override;
    void update() override;
    void reset() override;
    void enable() override;
    void getEvents() override;

    int getPoints()         override { return snake->points; }
    int getHighScore()      override { return snake->highScore; }
    int getPointsTarget()   override { return pointsTarget ; }
    bool isSnakeAlive()     override { return snake->alive(); }
    bool isWin()            override { return win; };
    void togglePause()      override { snake->isPaused = !snake->isPaused; }

    float getLevelSpeed()   override { return levelSpeed;  }
    void setLevelSpeed(float levelSpeed) { this->levelSpeed = 1 / levelSpeed; }

    void setBoardBorderSize(int size);
    void setBoardSize(int width, int height);
    void setBoardCellSize(int width, int height);
    void setBoardTopLeft(int x, int y);
    void setBorderColor(Color color);
    void setBoardCellBackgroundColor(Color color);
    void centerBoard();

    void setFoodSize(float radius);
    void setFoodColor(Color color);
    void setFoodCount(int count);

    void setSnakeStartSize(int size);
    //void setSnakeBodyPartSize(int width, int height);
    void setSnakeStartingPosition(int x, int y); // HEAD POSITION
    void setSnakeStartingDirection(Direction direction);
    void setSnakeHeadColor(Color color);
    void setSnakeBodyColor(Color color);

};

#endif
