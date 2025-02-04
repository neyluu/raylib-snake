#include "board.h"

Board::Board(int width, int height, Vector2 boardCellSize, Vector2 topLeft)
{
    this->width = width;
    this->height = height;
    this->cellSize = boardCellSize;
    this->topLeft = topLeft;

    this->playBoard = new Vector2*[this->height];
    for(int i = 0; i < this->height; i++)
    {
        this->playBoard[i] = new Vector2[this->width];
    }

    initBoard();
}

Board::~Board()
{
    for(int i = 0; i < height; i++)
    {
        delete playBoard[i];
    }
    delete playBoard;
}

void Board::setCellBorderColor(Color color)
{
    cellBorderColor = color;
}

void Board::centerInWindow(int windowWidth, int windowHeight)
{
    int playBoardX = width * cellSize.x;
    int playBoardY = height * cellSize.y;

    topLeft.x = (windowWidth - playBoardX) / 2;
    topLeft.y = (windowHeight - playBoardY) / 2;
}

void Board::draw()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            DrawRectangleLines(topLeft.x + playBoard[i][j].x, topLeft.y + playBoard[i][j].y, float(cellSize.x), float(cellSize.y),  cellBorderColor);
        }
    }
}

int Board::getWidth()
{
    return width;
}
int Board::getHeight()
{
    return height;
}


void Board::initBoard()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            playBoard[i][j].x = j * cellSize.x;
            playBoard[i][j].y = i * cellSize.y;
        }
    }
}
