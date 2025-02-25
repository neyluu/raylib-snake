#include "gui.h"

#include <iostream>

//void Gui::getEvents()
//{
//    for(Button button : buttons)
//    {
//        button.isClicked();
//    }
//}
void Gui::draw()
{
    drawButtons();
    drawPopups();
}

void Gui::drawButtons()
{
    for(auto &[key, value] : buttons)
    {
        if(value.isVisible) value.draw();
    }
}
void Gui::drawPopups()
{
    for(auto &[key, value] : popups)
    {
        if(value.isVisible) value.draw();
    }
}

void Gui::drawCounter(int x, int y, const std::string &text, int value)
{
    std::string toDraw = text;
    toDraw += std::to_string(value);
    DrawText(toDraw.c_str(), x, y, 30, RED);
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

bool Gui::isButtonClicked(const std::string &name)
{
    return buttons.at(name).isClicked();
}

void Gui::addButton(const std::string &name, Button button)
{
    buttons.insert(std::make_pair(name, button));
}
void Gui::addPopup(const std::string &name, Popup popup)
{
    popups.insert(std::make_pair(name, popup));
}
void Gui::setButtonVisibility(const std::string &name, bool visibility)
{
    buttons.at(name).isVisible = visibility;
}
void Gui::setPopupVisibility(const std::string& name, bool visibility)
{
    popups.at(name).setIsVisible(visibility);
}