#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "raylib.h"

class Board {
private:
    int width = 0;
    int height = 0;

    Color cellBorderColor = {0, 0, 0, 0};
    Vector2 topLeft = {0, 0};
    Vector2 cellSize = {0, 0};

    void initBoard();
public:
    Vector2 **playBoard = nullptr; // position of top left pixel of every cell

    Board() = default;
    Board(int width, int height, Vector2 boardCellSize, Vector2 topLeft);
    ~Board();

    void setCellBorderColor(Color color);
    void centerInWindow(int windowWidth, int windowHeight);
    void drawRectInCell(int x, int y, int width, int height, Color color, bool isInCenter, int offsetX, int offsetY);
    void drawCircleInCell(int x, int y, float radius, Color color);
    void draw();

    int getWidth();
    int getHeight();
};

#endif //BOARD_H
