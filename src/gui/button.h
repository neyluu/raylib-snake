#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

class Button {
private:
    Rectangle shape;
    Color color;
    char *text;
public:
    bool isVisible = true;
    Button(Rectangle shape, Color color, const char *text);


    bool isClicked();
    void draw();
};

#endif //BUTTON_H
