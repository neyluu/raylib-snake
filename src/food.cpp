#include "food.h"

Food::Food(Board *board)
{
    if(board == nullptr)
    {
        std::cout << "ERROR [ FOOD ] : board pointer is NULL!" << std::endl;
    }

    this->board = board;
}

void Food::init()
{
    spawn();
}

void Food::setBoard(Board *board)
{
    this->board = board;
}

void Food::draw()
{
    board->drawCircleInCell(position.x, position.y, radius, color);
}

Vector2 Food::getPosition()
{
    return position;
}

void Food::spawn()
{
    int posX = rand() % (board->getWidth());
    int posY = rand() % (board->getHeight());
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