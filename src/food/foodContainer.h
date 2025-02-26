#ifndef RAYLIB_SNAKE_FOODCONTAINER_H
#define RAYLIB_SNAKE_FOODCONTAINER_H

#include <vector>

#include "food.h"

class FoodContainer
{
private:
    std::vector<Food> foods;
    Board *board = nullptr;
public:
    FoodContainer(Board *board);

    void init();
    void draw();
    void addFood(const Food &food);
    void fill(int count, const Food &food);
    void clear();
    void spawnAll();
    bool exist(int x, int y);
    int getSize();
    Food *getFood(int index);
    Food *getFood(int x, int y);
};


#endif //RAYLIB_SNAKE_FOODCONTAINER_H
