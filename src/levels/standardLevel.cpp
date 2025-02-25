#include "standardLevel.h"

StandardLevel::~StandardLevel()
{
    delete board;
    delete food;
    delete snake;
}

StandardLevel::StandardLevel(double *tickRate)
{
    this->tickRate = tickRate;
    food->init();
    snake->init();
}

void StandardLevel::init()
{
    // TODO do stuff
}

void StandardLevel::draw()
{
    board->draw();
    food->draw();
    snake->draw(*tickRate * levelSpeed);
}
void StandardLevel::update()
{
    snake->update();
    if(snake->points == foodCount)
    {
        win = true;
        std::cout << "WIN\n";
    }
}
void StandardLevel::reset()
{
    snake->reset();
}
void StandardLevel::getEvents()
{
    snake->getEvent();
}


void StandardLevel::setBoardBorderSize(int size)
{
    board->setBorderSize(size);
}
void StandardLevel::setBoardSize(int width, int height)
{
    board->setBoardSize(width, height);
}
void StandardLevel::setBoardCellSize(int width, int height)
{
    board->setCellSize(Vector2(width, height));
}
void StandardLevel::setBoardTopLeft(int x, int y)
{
    board->setTopLeft(Vector2(x, y));
}
void StandardLevel::setBorderColor(Color color)
{
    board->setCellBorderColor(color);
}
void StandardLevel::setBoardCellBackgroundColor(Color color)
{
    board->setCellBackgroundColor(color);
}
void StandardLevel::centerBoard()
{
    board->center();
}


void StandardLevel::setFoodSize(float radius)
{
    food->setRadius(radius);
}
void StandardLevel::setFoodColor(Color color)
{
    food->setColor(color);
}
void StandardLevel::setSnakeStartSize(int size)
{
    snake->setStartSize(size);
}
//void StandardLevel::setSnakeBodyPartSize(int width, int height)
//{
//    snake->setBodyPartSize(width, height);
//}
void StandardLevel::setSnakeStartingPosition(int x, int y)
{
    snake->setStartingPosition(Vector2(x, y));
}
void StandardLevel::setSnakeStartingDirection(Direction direction)
{
    snake->setStartingDirection(direction);
}
void StandardLevel::setSnakeHeadColor(Color color)
{
    snake->setHeadColor(color);
}
void StandardLevel::setSnakeBodyColor(Color color)
{
    snake->setBodyColor(color);
}