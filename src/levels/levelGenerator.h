#ifndef RAYLIB_SNAKE_LEVELGENERATOR_H
#define RAYLIB_SNAKE_LEVELGENERATOR_H

#include "levels.h"
#include "../utils.h"
#include "../raylibExtra.h"

struct StandardLevelBoundaries
{
    int maxBoardSizeX = 700; // px
    int maxBoardSizeY = 570; // px

    int minBoardWidth = 5;
    int maxBoardWidth = 20;

    int minBoardHeight = 5;
    int maxBoardHeight = 20;

    int maxBorderSize = 5;

    int minCellSize = 30;
    int maxCellSize = 100; // Non square cells cause animation stuttering

    int maxFoodCount = 10;

    int minSnakeSize = 3;
    int maxSnakeSize = 10;
};

class LevelGenerator
{
private:
    inline static StandardLevelBoundaries boundaries;
public:
    static Level *generateStandardLevel(double *tickRate)
    {
        StandardLevel *lvl = new StandardLevel(tickRate);
        lvl->enable();
        LOG(L_NONE, "==== GENERATING LEVEL ====")

        // Generating board;
        int boardWidth =    Utils::randInt(boundaries.minBoardWidth, boundaries.maxBoardWidth);
        int boardHeight =   Utils::randInt(boundaries.minBoardHeight, boundaries.maxBoardHeight);
        lvl->setBoardSize(boardWidth, boardHeight);
        LOG(L_NONE, "Board size: " << boardWidth << " " << boardHeight)

        int maxCellX = boundaries.maxBoardSizeX / boardWidth;
        int maxCellY = boundaries.maxBoardSizeY / boardHeight;
        int maxCellSize;
        if(maxCellY > boundaries.maxCellSize && maxCellX > boundaries.maxCellSize)
        {
            maxCellSize = boundaries.maxCellSize;
        }
        else
        {
            maxCellSize = (maxCellX < maxCellY) ? maxCellX : maxCellY;
        }
        int cellSize = Utils::randInt(boundaries.minCellSize, maxCellSize);
        lvl->setBoardCellSize(cellSize, cellSize);
        LOG(L_NONE, "Cell size: " << cellSize)

        int borderSize = Utils::randInt(2, boundaries.maxBorderSize); // TODO max border size with small cell size cause strange board
        lvl->setBoardBorderSize(borderSize);
        LOG(L_NONE, "Border size: " << borderSize)

        // Colors;
        Color borderColor = Utils::randColor();
        lvl->setBorderColor(borderColor);
        LOG(L_NONE, "Border color: " << borderColor)

        Color cellColor = Utils::randColor();
        lvl->setBoardCellBackgroundColor(cellColor);
        LOG(L_NONE, "Cell color: " << cellColor)

        lvl->centerBoard();
        LOG(L_NONE, "Centering board")

        // FOOD

        const int minFoodCount = 1;
//        const int maxFoodCount = boardWidth * boardHeight - boundaries.minSnakeSize;
        int foodCount = Utils::randInt(minFoodCount, boundaries.maxFoodCount);
        lvl->setFoodCount(foodCount);
        LOG(L_NONE, "Food count: " << foodCount)

        const int minFoodSize = ((cellSize - borderSize) / 2) / 2;
        const int maxFoodSize = (cellSize - borderSize) / 2;
        int foodSize = Utils::randInt(minFoodSize, maxFoodSize);
        lvl->setFoodSize(foodSize);
        LOG(L_NONE, "Food size: " << foodSize)

        Color foodColor = Utils::randColor();
        lvl->setFoodColor(foodColor);
        LOG(L_NONE, "Food color" << foodColor)

        //==========
        // TODO implementation
        lvl->setSnakeStartSize(3);
        lvl->setSnakeStartingPosition(2, 0);
        lvl->setSnakeStartingDirection(RIGHT);
        //==========

        Color headColor = Utils::randColor();
        lvl->setSnakeHeadColor(headColor);
        LOG(L_NONE, "Head color: " << headColor)

        Color bodyColor = Utils::randColor();
        lvl->setSnakeBodyColor(bodyColor);
        LOG(L_NONE, "Body color: " << bodyColor)

        double levelSpeed = Utils::randInt(8, 20) / 10.0;
        lvl->setLevelSpeed(levelSpeed);
        LOG(L_NONE, "Level speed: " << levelSpeed)

//        int minPointsTarget = boardHeight * boardWidth / 2;
//        int maxPointsTarget = boardHeight * boardWidth - 5;
        //TODO tmp ========================
        int minPointsTarget = 2;
        int maxPointsTarget = 5;
        // ===============================
        int pointsTarget = Utils::randInt(minPointsTarget, maxPointsTarget);
        lvl->pointsTarget = pointsTarget;
        LOG(L_NONE, "Point target: " << pointsTarget)

        LOG(L_NONE, "==========================")
        return lvl;
    }
};

#endif //RAYLIB_SNAKE_LEVELGENERATOR_H
