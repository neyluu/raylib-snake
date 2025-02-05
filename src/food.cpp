#include "food.h"

void Food::init()
{
    int posX = rand() % (board->getWidth() + 1);
    int posY = rand() % (board->getHeight() + 1);
    position.x = posX;
    position.y = posY;

    radius = 8;
}

void Food::setBoard(Board *board)
{
    this->board = board;
}

void Food::draw()
{
    board->drawCircleInCell(position.x, position.y, radius, color);
}