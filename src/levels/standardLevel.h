#ifndef RAYLIB_SNAKE_STANDARDLEVEL_H
#define RAYLIB_SNAKE_STANDARDLEVEL_H

#include "level.h"

class StandardLevel : public virtual Level
{
private:
    int x = 5;
public:
    StandardLevel(int x) : x(x) {}
    void draw() override
    {

    }
    void test() override
    {
        std::cout << "Standard: ";
        std::cout << x << std::endl;
    }
};


#endif
