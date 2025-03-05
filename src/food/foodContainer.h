#ifndef RAYLIB_SNAKE_FOODCONTAINER_H
#define RAYLIB_SNAKE_FOODCONTAINER_H

#include <vector>
#include "food.h"
#include "../utils.h"

class FoodContainer
{
public:
    int getSize() const;
    Food *getFood(int index);
    Food *getFood(int x, int y);

    void setFoodSize(int radius);
    void setFoodColor(Color color);

    void addFood(const Food &food);
    void fill(int count, const Food &food);
    bool exist(int x, int y);

    void init();
    void draw();
    void clear();
    void spawnAll();
private:
    std::vector<Food> foods;
};

#endif
