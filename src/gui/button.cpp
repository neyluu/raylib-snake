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
    if(mouseInButton()) return true;
    return false;
}

bool Button::mouseInButton()
{
    Vector2 mousePos = GetMousePosition();

    if(mousePos.x >= shape.x && mousePos.x <= shape.x + shape.width &&
       mousePos.y >= shape.y && mousePos.y <= shape.y + shape.height)
    {
        return true;
    }
    return false;
}