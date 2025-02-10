#ifndef RAYLIB_SNAKE_EVENTS_H
#define RAYLIB_SNAKE_EVENTS_H

#include <map>


struct Events
{
    bool Game_reset = false;

    void setDefault()
    {
        Game_reset = false;
    }
};

#endif
