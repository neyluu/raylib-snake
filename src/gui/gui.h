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

//    std::vector<Button> buttons;
    std::map<std::string, Popup> popups;
    std::map<std::string, Button> buttons;

    void drawButtons();
    void drawPopups();
public:
    void draw();
//    void getEvents();

    void drawScore(int score);
    void drawHighScore(int highScore);

    void drawCounter(int x, int y, const std::string &text, int value);

    bool isButtonClicked(const std::string &name);
    void setButtonVisibility(const std::string &name, bool visibility);

    void addButton(const std::string &name, Button button);
    void addPopup(const std::string &name, Popup popup);
    void setPopupVisibility(const std::string& name, bool visibility);
};

#endif //GUI_H
