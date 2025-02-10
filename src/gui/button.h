#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include "events.h"

class Button {
private:
    Rectangle shape;
    Color color;
    char *text;
    bool *event;
public:
    Button(Rectangle shape, Color color, const char *text, bool *event);

    // TODO get somehow pointer to method that should be called when button is pressed
    // TODO then by just calling isClicked in loop, every event will be handled
    bool isClicked();
    void draw();

};

#endif //BUTTON_H
