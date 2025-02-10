#include "popup.h"

#include "../settings.h"

Popup::Popup(Rectangle shape, Color color, const char *text, int fontSize, Color fontColor)
{
    this->shape = shape;
    this->color = color;
    this->text = (char*) text;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
}

void Popup::draw()
{
    DrawRectangleRec(shape, color);

    int textLen = MeasureText(text, fontSize);
    DrawText(text,
             settings.screenWidth / 2 - textLen / 2,
             settings.screenHeight / 2 - fontSize / 2,
             fontSize, fontColor);
}

void Popup::setIsVisible(bool isVisible)
{
    this->isVisible = isVisible;
}
