#ifndef GUI_H
#define GUI_H

#include <string>


#include "../settings.h"
#include "raylib.h"

class Gui {
private:
    const int gameOverWidth = 300;
    const int gameOverHeight = 150;
    const int gameOverFontSize = 30;
    const Color gameOverBackgroundColor = WHITE;
    const Color gameOverTextColor = BLACK;

public:
    void drawGameOver();
    void drawScore(int score);
};

#endif //GUI_H
