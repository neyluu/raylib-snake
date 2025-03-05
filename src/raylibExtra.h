#ifndef RAYLIB_SNAKE_RAYLIBEXTRA_H
#define RAYLIB_SNAKE_RAYLIBEXTRA_H

#include <iostream>
#include "raylib.h"

inline std::ostream& operator<<(std::ostream &out, const Color &color)
{
    out << "(" << int(color.r) << " " << int(color.g) << " " << int(color.b) << " " << int(color.a) << ")";
    return out;
}

#endif //RAYLIB_SNAKE_RAYLIBEXTRA_H
