#ifndef RAYLIB_SNAKE_LEVEL_H
#define RAYLIB_SNAKE_LEVEL_H

#include <iostream>

class Level
{
private:
    int x = 0;
public:
    virtual void draw() = 0;
    virtual void test() = 0;
};

#endif
