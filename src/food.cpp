#include "food.h"

void Food::init()
{
    spawn();
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

Vector2 Food::getPosition()
{
    return position;
}

void Food::spawn()
{
    std::cout << time(NULL) << "Spawning food" << std::endl;
    int posX = rand() % (board->getWidth());
    int posY = rand() % (board->getHeight());
    position.x = posX;
    position.y = posY;
}
