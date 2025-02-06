#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

class Button {
private:
    Rectangle shape;
    Color color;
    char *text;

    bool mouseInButton();
public:
    Button(Rectangle shape, Color color, const char *text);

    // TODO get somehow pointer to method that should be called when button is pressed
    // TODO then by just calling isClicked in loop, every event will be handled
    bool isClicked();
    void draw();
};

#endif //BUTTON_H
