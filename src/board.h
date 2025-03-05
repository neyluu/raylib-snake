#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include "raylib.h"
#include "direction.h"
#include "settings.h"
#include "utils.h"

class Board
{
public:
    Vector2 **playBoard = nullptr; // Position of top left pixel of every cell

    Board();
    Board(int width, int height, Vector2 cellSize, Vector2 topLeft);
    ~Board();

    static void setCurrent(Board *board);
    static Board* getCurrent();

    int getWidth() const;
    int getHeight() const;
    int getBorderSize() const;
    Vector2 getCellSize() const;
    Vector2 getTopLeft() const;
    Vector2 getCellPosition(int x, int y) const;

    void setBorderSize(int size);
    void setBoardSize(int width, int height);
    void setCellBorderColor(Color color);
    void setCellBackgroundColor(Color color);
    void setCellSize(Vector2 cellSize);
    void setTopLeft(Vector2 topleft);
    void center();

    void draw();
    void drawRectInCell(int x, int y, int width, int height, Color color, bool isInCenter, int offsetX, int offsetY);
    void drawCircleInCell(int x, int y, float radius, Color color);
    void drawTriangleDir(int x, int y, Direction direction, Color color);
protected:
    inline static Board *current; // Only one board should be displayed at time
private:
    int width = 1;
    int height = 1;
    int roundness = 3;
    int borderSize = 5;
    Color borderColor = BLACK;
    Color cellBackgroundColor = WHITE;
    Vector2 topLeft = { 0, 0 };
    Vector2 cellSize = { 10, 10 };

    Texture2D texture;

    void destroyPlayBoard();
    void initBoard();
    void createCellData();
    void createTexture();
};

#endif
