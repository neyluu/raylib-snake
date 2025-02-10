#ifndef SETTINGS_H
#define SETTINGS_H

#include "raylib.h"

struct Keymap
{
    int moveUp = KEY_W;
    int moveRight = KEY_D;
    int moveDown = KEY_S;
    int moveLeft = KEY_A;

    int resetGame = KEY_R;
    int pauseGame = KEY_P;
    int exitGame = KEY_ESCAPE;
};

class Settings {
public:
    int screenWidth = 800;
    int screenHeight = 600;

    Keymap keymap;
};

inline Settings settings;

#endif //SETTINGS_H
