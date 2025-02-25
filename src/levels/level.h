#ifndef RAYLIB_SNAKE_LEVEL_H
#define RAYLIB_SNAKE_LEVEL_H

#include <iostream>

class Level
{
public:
    virtual ~Level() { }

    virtual void init() = 0;
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void reset() = 0;
    virtual void getEvents() = 0;

    virtual float getLevelSpeed() = 0;
    virtual int getPoints() = 0;
    virtual int getHighScore() = 0;
    virtual bool isSnakeAlive()  = 0;
    virtual bool isWin() = 0;
    virtual void togglePause() = 0 ;
};

#endif
