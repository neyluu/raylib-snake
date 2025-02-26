#include "foodContainer.h"

FoodContainer::FoodContainer(Board *board)
{
    this->board = board;
}

void FoodContainer::init()
{
    spawnAll();
}

void FoodContainer::draw()
{
    for(Food food : foods)
    {
        food.draw();
    }
}
void FoodContainer::addFood(const Food &food)
{
    foods.push_back(food);
}
void FoodContainer::fill(int count, const Food &food)
{
    if(foods.size() != 0) foods.clear();

    for(int i = 0; i < count; i++)
    {
        foods.push_back(food);
    }
}
void FoodContainer::clear()
{
    foods.clear();
}

void FoodContainer::spawnAll()
{
    Food newFood(board);
    newFood = foods[0];

    int iterations = 0;
    const int MAX_ITERATIONS = 1000;

    for(int i = 0; i < foods.size(); i++)
    {
        iterations = 0;
        do {
            newFood.spawn();
            iterations++;
            if(iterations == MAX_ITERATIONS)
            {
                std::cout << "ERROR [ FoodContainer ]: Spawning food hit iteration limit!" << std::endl;
                break;
            }
        } while(exist(newFood.getPosition().x, newFood.getPosition().y));
        foods[i] = newFood;
    }
}

bool FoodContainer::exist(int x, int y)
{
    for(Food food : foods)
    {
        if(food.getPosition().x == x && food.getPosition().y == y)
            return true;
    }
    return false;
}

int FoodContainer::getSize()
{
    return foods.size();
}
Food* FoodContainer::getFood(int index)
{
    if(index < 0 || index >= foods.size()) return nullptr;
    return &foods[index];
}
Food* FoodContainer::getFood(int x, int y)
{
    for(int i = 0; i < foods.size(); i++)
    {
        if(foods[i].getPosition().x == x && foods[i].getPosition().y == y)
            return &foods[i];
    }
    return nullptr;
}
void FoodContainer::setFoodSize(int radius)
{
    for(Food &food : foods)
    {
        food.setRadius(radius);
    }
}
void FoodContainer::setFoodColor(Color color)
{
    for(Food &food : foods)
    {
        food.setColor(color);
    }
}