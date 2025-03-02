#ifndef RAYLIB_SNAKE_UTILS_H
#define RAYLIB_SNAKE_UTILS_H

#include <iostream>
#include <ctype.h>

#include "raylib.h"

namespace Utils
{
    static int randInt(int min, int max)
    {
        if(min == max) return max;
        return min + rand() % (max - min);
    }

    static Color randColor()
    {
        unsigned char r = Utils::randInt(0, 255);
        unsigned char g = Utils::randInt(0, 255);
        unsigned char b = Utils::randInt(0, 255);
        unsigned char a = 255;

        return { r, g, b, a };
    }
    static Color randColorAlpha()
    {
        Color color = Utils::randColor();
        color.a = Utils::randInt(0, 255);

        return color;
    }
}

#endif
