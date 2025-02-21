#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "raylib.h"
#include "direction.h"
#include "settings.h"

class Board
{
private:
    int width = 1;
    int height = 1;
    int borderSize = 5;
    Color borderColor = BLACK;
    Color cellBackgroundColor = WHITE;
    Vector2 topLeft = {0, 0};
    Vector2 cellSize = {10, 10};

    void destroyPlayBoard();
    void initBoard();
    void createCellData();
public:
    Vector2 **playBoard = nullptr; // position of top left pixel of every cell

    Board();
    Board(int width, int height, Vector2 cellSize, Vector2 topLeft);
    ~Board();

    void drawRectInCell(int x, int y, int width, int height, Color color, bool isInCenter, int offsetX, int offsetY);
    void drawCircleInCell(int x, int y, float radius, Color color);
    void drawTriangleDir(int x, int y, Direction direction, Color color);
    void draw();

    int getWidth();
    int getHeight();
    Vector2 getCellSize();

    void setBorderSize(int size);
    void setBoardSize(int width, int height);
    void setCellBorderColor(Color color);
    void setCellBackgroundColor(Color color);
    void setCellSize(Vector2 cellSize);
    void setTopLeft(Vector2 topleft);
    void center();
};

#endif //BOARD_H
