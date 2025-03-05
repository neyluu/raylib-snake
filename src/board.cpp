#include "board.h"

Board::Board()
{
    Board::current = nullptr;
    initBoard();
}
Board::Board(int width, int height, Vector2 cellSize, Vector2 topLeft)
{
    Board::current = nullptr;
    this->width = width;
    this->height = height;
    this->cellSize = cellSize;
    this->topLeft = topLeft;

    initBoard();
    createTexture();
}
Board::~Board()
{
    destroyPlayBoard();
    UnloadTexture(texture);
}


void Board::setCurrent(Board *board)
{
    Board::current = board;
}
Board* Board::getCurrent()
{
    return Board::current;
}


int Board::getWidth() const
{
    return width;
}
int Board::getHeight() const
{
    return height;
}
int Board::getBorderSize() const
{
    return borderSize;
}
Vector2 Board::getCellSize() const
{
    return cellSize;
}
Vector2 Board::getTopLeft() const
{
    return topLeft;
}
Vector2 Board::getCellPosition(int x, int y) const
{
    return playBoard[x][y];
}


void Board::setBorderSize(int size)
{
    borderSize = size;
    createCellData();
    createTexture();
}
void Board::setBoardSize(int width, int height)
{
    if(playBoard != nullptr) destroyPlayBoard();

    this->width = width;
    this->height = height;

    initBoard();
    createTexture();
}
void Board::setCellSize(Vector2 cellSize)
{
    this->cellSize = cellSize;

    createCellData();
    createTexture();
}
void Board::setTopLeft(Vector2 topleft)
{
    this->topLeft = topleft;
}
void Board::setCellBorderColor(Color color)
{
    borderColor = color;
    createTexture();
}
void Board::setCellBackgroundColor(Color color)
{
    cellBackgroundColor = color;
    createTexture();
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
    DrawTexture(texture, topLeft.x - borderSize, topLeft.y - borderSize, WHITE);
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
    int offsetX = (cellSize.x - borderSize) / 2;
    int offsetY = (cellSize.y - borderSize) / 2;

    DrawCircle(topLeft.x + playBoard[x][y].x + offsetX, topLeft.y + playBoard[x][y].y + offsetY, radius, BLACK);
    DrawCircle(topLeft.x + playBoard[x][y].x + offsetX, topLeft.y + playBoard[x][y].y + offsetY, radius - 2, color);
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

            // Debug
//            std::cout << "(" << playBoard[i][j].x << " " << playBoard[i][j].y << ") ";
        }
//        std::cout << std::endl;
    }
}
void Board::createTexture()
{
    Image img = GenImageColor(width * cellSize.x + borderSize,height * cellSize.x + borderSize,borderColor);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

            ImageDrawRectangle(&img,
                                (j + 1) * borderSize + j * (cellSize.x - borderSize) + roundness,
                               (i + 1) * borderSize + i * (cellSize.x - borderSize),
                               (cellSize.x - borderSize) - roundness * 2,
                               cellSize.x - borderSize,
                               cellBackgroundColor
                            );
            ImageDrawRectangle(&img,
                                borderSize + j * cellSize.x,
                               borderSize + i * cellSize.x + roundness,
                               cellSize.x - borderSize,
                               (cellSize.x - borderSize)- roundness * 2,
                               cellBackgroundColor
                            );
            ImageDrawCircle(&img,
                            borderSize + j * cellSize.x + roundness,
                            borderSize + i * cellSize.x + roundness,
                            roundness,
                            cellBackgroundColor);
            ImageDrawCircle(&img,
                            j * cellSize.x + roundness + cellSize.x - roundness * 2,
                            borderSize + i * cellSize.x + roundness,
                            roundness,
                            cellBackgroundColor);
            ImageDrawCircle(&img,
                            j * cellSize.x + roundness + cellSize.x - roundness * 2,
                             i * cellSize.x + roundness + cellSize.x - roundness * 2 - 1,
                            roundness,
                            cellBackgroundColor);
            ImageDrawCircle(&img,
                            borderSize + j * cellSize.x + roundness,
                             i * cellSize.x + roundness + cellSize.x - roundness * 2 - 1,
                            roundness,
                            cellBackgroundColor);
        }
    }

    texture = LoadTextureFromImage(img);
}
