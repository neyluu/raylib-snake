#ifndef FOOD_H
#define FOOD_H

#include "../board.h"

class Food
{
private:
    float radius = 0.0;
    Color color = RED;
    Vector2 position = {0, 0};
public:

    void init();
    void draw();
    void spawn();

    Vector2 getPosition();

    void setRadius(float radius);
    void setColor(Color color);
};

#endif //FOOD_H
