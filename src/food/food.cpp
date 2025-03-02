#include "food.h"

void Food::init()
{
    spawn();
}

void Food::draw()
{
    int offsetX = (Board::getCurrent()->getCellSize().x - Board::getCurrent()->getBorderSize()) / 2;
    int offsetY = (Board::getCurrent()->getCellSize().y - Board::getCurrent()->getBorderSize()) / 2;

    DrawCircle(Board::getCurrent()->getTopLeft().x + Board::getCellPosition(position.x, position.y).x + offsetX,
               Board::getCurrent()->getTopLeft().y + Board::getCellPosition(position.x, position.y).y + offsetY,
               radius,
               Color(50, 50, 50, 200)
           );

    DrawCircle(Board::getCurrent()->getTopLeft().x + Board::getCellPosition(position.x, position.y).x + offsetX,
               Board::getCurrent()->getTopLeft().y + Board::getCellPosition(position.x, position.y).y + offsetY,
               radius - 2,
               color
    );
}

Vector2 Food::getPosition()
{
    return position;
}

void Food::spawn()
{
    int posX = rand() % (Board::getCurrent()->getHeight());
    int posY = rand() % (Board::getCurrent()->getWidth());

    position.x = posX;
    position.y = posY;
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