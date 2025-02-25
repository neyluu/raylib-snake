#include "button.h"

Button::Button(Rectangle shape, Color color, const char *text)
{
    this->shape = shape;
    this->color = color;
    this->text = (char*) text;
}

void Button::draw()
{
    DrawRectangleRec(shape, color);
    int textLen = MeasureText(text, 30);
    DrawText(text, shape.x + shape.width / 2 - textLen / 2, shape.y + shape.height / 2 - 15, 30, BLACK);
}

bool Button::isClicked()
{
    if(CheckCollisionPointRec(GetMousePosition(), shape) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        return true;

    return false;
}