#ifndef RAYLIB_SNAKE_EVENTS_H
#define RAYLIB_SNAKE_EVENTS_H

#include <map>


struct Events
{
    bool Game_reset = false;
    bool Game_pause = false;

    void setDefault()
    {
        Game_reset = false;
        Game_pause = true;
    }
};

#endif
