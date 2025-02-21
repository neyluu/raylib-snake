#include "standardLevel.h"

StandardLevel::~StandardLevel()
{
    delete board;
    delete food;
//    delete snake;
}

StandardLevel::StandardLevel(double *tickRate)
{
    this->tickRate = tickRate;

    //board->centerInWindow(settings.screenWidth, settings.screenHeight);
//    board->setCellBorderColor(Color(200, 20, 20, 255));

//    food->setBoard(&board);
    food->init();

//    snake.setBoard(&board);
//    snake.setFood(&food);
//    snake->init();
}

void StandardLevel::init()
{
    // TODO do stuff
}

void StandardLevel::draw()
{
    board->draw();
    food->draw();
//    snake->draw(*tickRate);
}
void StandardLevel::update()
{
//    snake->update();
}
void StandardLevel::reset()
{
//    snake->reset();
}
void StandardLevel::getEvents()
{
//    snake->getEvent();
}

void StandardLevel::setBoardBorderSize(int size)
{
    board->setBorderSize(size);
}
void StandardLevel::setBoardSize(int width, int height)
{
    board->setBoardSize(width, height);
}
void StandardLevel::setCellSize(int width, int height)
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
void StandardLevel::setCellBackgroundColor(Color color)
{
    board->setCellBackgroundColor(color);
}
void StandardLevel::centerBoard()
{
    board->center();
}
