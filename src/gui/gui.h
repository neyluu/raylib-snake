#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>

#include "raylib.h"
#include "../settings.h"
#include "button.h"

class Gui {
private:
    const int gameOverWidth = 300;
    const int gameOverHeight = 150;
    const int gameOverFontSize = 30;
    const Color gameOverBackgroundColor = WHITE;
    const Color gameOverTextColor = BLACK;

    std::vector<Button> buttons;
public:
    void getEvents();
    void drawButtons();

    void drawGameOver();
    void drawScore(int score);

    void addButton(Button button);
};

#endif //GUI_H
