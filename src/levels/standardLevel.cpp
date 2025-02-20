#include "standardLevel.h"

StandardLevel::StandardLevel(double *tickRate)
{
    this->tickRate = tickRate;

    board.centerInWindow(settings.screenWidth, settings.screenHeight);
    board.setCellBorderColor(Color(200, 20, 20, 255));

    food.setBoard(&board);
    food.init();

    snake.setBoard(&board);
    snake.setFood(&food);
    snake.init();
}

void StandardLevel::draw()
{
    board.draw();
    food.draw();
    snake.draw(*tickRate);
}
void StandardLevel::update()
{
    snake.update();
}
void StandardLevel::reset()
{
    snake.reset();
}
void StandardLevel::getEvents()
{
    snake.getEvent();
}