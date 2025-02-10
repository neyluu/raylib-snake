#ifndef RAYLIB_SNAKE_POPUP_H
#define RAYLIB_SNAKE_POPUP_H

#include "raylib.h"

class Popup {
private:

    Rectangle shape;
    Color color;
    Color fontColor;
    char *text;
    int fontSize;
public:
    bool isVisible = false;

    Popup(Rectangle shape, Color color, const char *text, int fontSize, Color fontColor);

    void draw();
    void setIsVisible(bool isVisible);
};


#endif
