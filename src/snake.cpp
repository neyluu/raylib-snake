#include "snake.h"

void Snake::draw()
{
    board->drawRectInCell(6, 6, 20, 20, BLUE, true, 0, 0);
}
void Snake::update()
{

}

void Snake::setBoard(Board *board)
{
    this->board = board;
}