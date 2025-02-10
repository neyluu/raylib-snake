#ifndef GUI_H
#define GUI_H

#include <string>
#include <vector>
#include <map>

#include "raylib.h"
#include "../settings.h"
#include "button.h"
#include "popup.h"

class Gui {
private:
    const int gameOverWidth = 300;
    const int gameOverHeight = 150;
    const int gameOverFontSize = 30;
    const Color gameOverBackgroundColor = WHITE;
    const Color gameOverTextColor = BLACK;

    std::vector<Button> buttons;
    std::map<std::string, Popup> popups;

    void drawButtons();
    void drawPopups();
public:
    void draw();
    void getEvents();

    void drawGameOver();
    void drawScore(int score);

    void addButton(Button button);
    void addPopup(const std::string &name, Popup popup);
    void setPopupVisibility(const std::string& name, bool visibility);
};

#endif //GUI_H
