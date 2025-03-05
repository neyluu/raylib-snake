#include "food.h"

Vector2 Food::getPosition() const
{
    return position;
}

void Food::setRadius(float radius)
{
    if(radius < 0) return;
    this->radius = radius;
}
void Food::setColor(Color color)
{
    this->color = color;
}

void Food::init()
{
    spawn();
}
void Food::draw()
{
    int offsetX = (Board::getCurrent()->getCellSize().x - Board::getCurrent()->getBorderSize()) / 2;
    int offsetY = (Board::getCurrent()->getCellSize().y - Board::getCurrent()->getBorderSize()) / 2;

    Vector2 topLeft = Board::getCurrent()->getTopLeft();
    Vector2 cellPos = Board::getCurrent()->getCellPosition(position.x, position.y);

    Color outlineColor = color;
    outlineColor.r = ((outlineColor.r - 30) < 0) ? 0 : outlineColor.r - 30;
    outlineColor.g = ((outlineColor.g - 30) < 0) ? 0 : outlineColor.g - 30;
    outlineColor.b = ((outlineColor.b - 30) < 0) ? 0 : outlineColor.b - 30;

    DrawCircle(topLeft.x + cellPos.x + offsetX, topLeft.y + cellPos.y + offsetY, radius, outlineColor);
    DrawCircle(topLeft.x + cellPos.x + offsetX, topLeft.y + cellPos.y + offsetY, radius - 2, color);
}
void Food::spawn()
{
    int posX = rand() % (Board::getCurrent()->getHeight());
    int posY = rand() % (Board::getCurrent()->getWidth());

    position.x = posX;
    position.y = posY;
}
