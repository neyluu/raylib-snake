#include "gui.h"

#include <iostream>

void Gui::getEvents()
{
    for(Button button : buttons)
    {
        button.isClicked();
    }
}
void Gui::draw()
{
    drawButtons();
    drawPopups();
}

void Gui::drawButtons()
{
    for(Button button : buttons)
    {
        button.draw();
    }
}
void Gui::drawPopups()
{
    for(auto &[key, value] : popups)
    {
        if(value.isVisible) value.draw();
    }
}
void Gui::drawGameOver()
{
    DrawRectangle(settings.screenWidth / 2 - (gameOverWidth / 2),
                  settings.screenHeight / 2 - (gameOverHeight / 2),
                       gameOverWidth, gameOverHeight, gameOverBackgroundColor);
    std::string text = "GAME OVER";
    int textLen = MeasureText(text.c_str(), gameOverFontSize);
    DrawText("GAME OVER",
         settings.screenWidth / 2 - textLen / 2,
         settings.screenHeight / 2 - gameOverFontSize / 2,
              gameOverFontSize, gameOverTextColor);
}
void Gui::drawScore(int score)
{
    std::string text = "SCORE: ";
    text += std::to_string(score);
    int textWidth = MeasureText(text.c_str(), 50);
    DrawText(text.c_str(), settings.screenWidth / 2 - textWidth / 2,10,50,RED);
}

void Gui::addButton(Button button)
{
    buttons.push_back(button);
}
void Gui::addPopup(const std::string &name, Popup popup)
{
    popups.insert(std::make_pair(name, popup));
}

void Gui::setPopupVisibility(const std::string& name, bool visibility)
{
    popups.at(name).setIsVisible(visibility);
}