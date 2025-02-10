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

void Gui::drawScore(int score)
{
    std::string text = "SCORE: ";
    text += std::to_string(score);
    DrawText(text.c_str(), settings.screenWidth / 2,30,30,RED);
}

void Gui::drawHighScore(int highScore)
{
    std::string text = "HIGH SCORE: ";
    text += std::to_string(highScore);
    DrawText(text.c_str(), 10,30,30,RED);
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