#include "board.h"

Board::Board()
{
    initBoard();
}

Board::Board(int width, int height, Vector2 cellSize, Vector2 topLeft)
{
    this->width = width;
    this->height = height;
    this->cellSize = cellSize;
    this->topLeft = topLeft;

    initBoard();
}

Board::~Board()
{
    destroyPlayBoard();
}

void Board::setCellBorderColor(Color color)
{
    borderColor = color;
}

void Board::center()
{
    int playBoardX = width * cellSize.x;
    int playBoardY = height * cellSize.y;

    topLeft.x = (settings.screenWidth - playBoardX) / 2;
    topLeft.y = (settings.screenHeight - playBoardY) / 2;
}

void Board::draw()
{
    DrawRectangleLines(topLeft.x, topLeft.y, width * cellSize.x + 1, height * cellSize.y + 1, borderColor);
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            DrawRectangleLinesEx(Rectangle(topLeft.x + playBoard[i][j].x, topLeft.y + playBoard[i][j].y, float(cellSize.x), float(cellSize.y)), 1, borderColor);
        }
    }
}

void Board::drawRectInCell(int x, int y, int width, int height, Color color, bool isInCenter, int offsetX, int offsetY)
{
    if(isInCenter)
    {
        offsetX = (cellSize.x - width) / 2;
        offsetY = (cellSize.y - height) / 2;
    }
    DrawRectangle(topLeft.x + playBoard[x][y].x + offsetX, topLeft.y + playBoard[x][y].y + offsetY, width, height, color);
}

void Board::drawCircleInCell(int x, int y, float radius, Color color)
{
    int offsetX = cellSize.x - radius * 2 + 1;
    int offsetY = cellSize.y - radius * 2 + 1;

    DrawCircle(topLeft.x + playBoard[x][y].x + offsetX, topLeft.y + playBoard[x][y].y + offsetY, radius, color);
}

void Board::drawTriangleDir(int x, int y, Direction direction, Color color)
{
    if(direction == UP)
    {
        DrawTriangle(Vector2(topLeft.x + playBoard[x][y].x + (cellSize.x / 2), topLeft.y + playBoard[x][y].y),
                     Vector2(topLeft.x + playBoard[x][y].x, topLeft.y + playBoard[x][y].y + cellSize.y),
                     Vector2(topLeft.x + playBoard[x][y].x + cellSize.x, topLeft.y + playBoard[x][y].y + cellSize.y),
                     color
                     );
    }
    else if(direction == RIGHT)
    {
        DrawTriangle(Vector2(topLeft.x + playBoard[x][y].x, topLeft.y + playBoard[x][y].y),
                     Vector2(topLeft.x + playBoard[x][y].x, topLeft.y + playBoard[x][y].y + cellSize.y),
                     Vector2(topLeft.x + playBoard[x][y].x + cellSize.x, topLeft.y + playBoard[x][y].y + (cellSize.y / 2)),
                     color
                     );
    }
    else if(direction == DOWN)
    {
        DrawTriangle(Vector2(topLeft.x + playBoard[x][y].x, topLeft.y + playBoard[x][y].y),
                     Vector2(topLeft.x + playBoard[x][y].x + (cellSize.x / 2), topLeft.y + playBoard[x][y].y + cellSize.y),
                     Vector2(topLeft.x + playBoard[x][y].x + cellSize.x, topLeft.y + playBoard[x][y].y),
                     color
                     );
    }
    else if(direction == LEFT)
    {
        DrawTriangle(Vector2(topLeft.x + playBoard[x][y].x + cellSize.x, topLeft.y + playBoard[x][y].y),
                     Vector2(topLeft.x + playBoard[x][y].x, topLeft.y + playBoard[x][y].y + (cellSize.y / 2)),
                     Vector2(topLeft.x + playBoard[x][y].x + cellSize.x, topLeft.y + playBoard[x][y].y + cellSize.y),
                     color
                     );
    }
    else return;
}

int Board::getWidth()
{
    return width;
}
int Board::getHeight()
{
    return height;
}
Vector2 Board::getCellSize()
{
    return cellSize;
}

void Board::destroyPlayBoard()
{
    if(playBoard == nullptr) return;
    for(int i = 0; i < height; i++)
    {
        delete [ ] playBoard[i];
    }
    delete [ ] playBoard;
}

void Board::initBoard()
{
    playBoard = new Vector2*[height];
    for(int i = 0; i < height; i++)
    {
        playBoard[i] = new Vector2[width];
    }

   createCellData();
}

void Board::createCellData()
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

void Board::setBoardSize(int width, int height)
{
    if(playBoard != nullptr) destroyPlayBoard();

    this->width = width;
    this->height = height;

    initBoard();
}
void Board::setCellSize(Vector2 cellSize)
{
    this->cellSize = cellSize;

    createCellData();
}