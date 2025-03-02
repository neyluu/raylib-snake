#ifndef FOOD_H
#define FOOD_H

#include "../board.h"

class Food
{
public:
    Vector2 getPosition() const;

    void setRadius(float radius);
    void setColor(Color color);

    void init();
    void draw();
    void spawn();
private:
    float radius = 0.0;
    Color color = RED;
    Vector2 position = { 0, 0 };
};

#endif //FOOD_H
