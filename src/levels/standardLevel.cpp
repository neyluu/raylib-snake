#include "standardLevel.h"

StandardLevel::~StandardLevel()
{
    delete board;
    delete snake;
    delete foods;
}

StandardLevel::StandardLevel(double *tickRate)
{
    this->tickRate = tickRate;

    Food food;
    food.setColor(RED);
    food.setRadius(15);
    foods->fill(1, food);
}

void StandardLevel::init()
{
    // TODO do stuff
}
void StandardLevel::enable()
{
    Board::setCurrent(board);
    foods->spawnAll();
    snake->init();
}
void StandardLevel::draw()
{
    board->draw();
    foods->draw();
    snake->draw(*tickRate * levelSpeed);
}
void StandardLevel::update()
{
    snake->update();
    if(snake->points == pointsTarget)
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
    foods->setFoodSize(radius);
}
void StandardLevel::setFoodColor(Color color)
{
    foods->setFoodColor(color);
}
void StandardLevel::setFoodCount(int count)
{
    if(foods->getSize() == count) return;

    Food *food = foods->getFood(0);
    if(foods->getSize() < count)
    {
        foods->clear();
        foods->fill(count, *food);
    }
    else
    {
        for(int i = 0; i < count - foods->getSize(); i++)
        {
            foods->addFood(*food);
        }
    }
//    foods->spawnAll();
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