#ifndef RAYLIB_SNAKE_STANDARDLEVEL_H
#define RAYLIB_SNAKE_STANDARDLEVEL_H

#include "level.h"

#include "../board.h"
#include "../snake.h"
#include "../food.h"

class StandardLevel : public Level
{
private:
//    Board *board = new Board(15, 15, Vector2(30,30), Vector2(0, 0));
    Board *board = new Board();
    Food *food = new Food(board);
//    Snake *snake = new Snake(board, food, 3, 28, 28, DARKBLUE, WHITE);

    float levelSpeed = 1;
    const double * tickRate = nullptr;
public:
    StandardLevel(double *tickRate);
    ~StandardLevel() override;

    void init() override;
    void draw() override;
    void update() override;
    void reset() override;
    void getEvents() override;

    int getPoints()     override { return 0; //snake->points;
     }
    int getHighScore()  override { return 0; //snake->highScore;
     }
    bool isSnakeAlive() override { return 0; //snake->alive();
    }
    void togglePause()  override { //snake->isPaused = !snake->isPaused;
    }

    void setBoardSize(int width, int height);
    void setBorderColor(Color color);
    void setCellSize(int width, int height);
    void centerBoard();
};


#endif
