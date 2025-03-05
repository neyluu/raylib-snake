#ifndef RAYLIB_SNAKE_UTILS_H
#define RAYLIB_SNAKE_UTILS_H

#include <iostream>
#include <ctype.h>

#include "raylib.h"

// To disable logging comment this flag
#define LOGGING

enum LogType
{
    L_NONE,
    L_INFO,
    L_WARNING,
    L_ERROR
};

#ifdef LOGGING
#define LOG(type, msg)                                                              \
do{                                                                                 \
if(type == L_INFO) std::cout << "INFO: ";                                           \
    if(type == L_WARNING) std::cout << __FILE__ << ":" << __LINE__ << " WARNING:";  \
    if(type == L_ERROR) std::cout << __FILE__ << ":" << __LINE__ << " ERROR: ";     \
    std::cout << msg << "\n";                                                       \
}while(0);
#else
#define LOG(type, msg) do { } while(0);
#endif

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
