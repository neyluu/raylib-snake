#ifndef RAYLIB_SNAKE_LEVELGENERATOR_H
#define RAYLIB_SNAKE_LEVELGENERATOR_H

#include "levels.h"
#include "../utils.h"

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

        std::cout << "==== GENERATING LEVEL ====" << std::endl;

        // Generating board;
        int boardWidth =    Utils::randInt(boundaries.minBoardWidth, boundaries.maxBoardWidth);
        int boardHeight =   Utils::randInt(boundaries.minBoardHeight, boundaries.maxBoardHeight);
        lvl->setBoardSize(boardWidth, boardHeight);
        std::cout << "Board size: " << boardWidth << " " << boardHeight << std::endl;

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
        std::cout << "Cell size: " << cellSize << std::endl;

        int borderSize = Utils::randInt(2, boundaries.maxBorderSize); // TODO max border size with small cell size cause strange board
        lvl->setBoardBorderSize(borderSize);
        std::cout << "Border size: " << borderSize << std::endl;

        // Colors;
        Color borderColor = Utils::randColor();
        lvl->setBorderColor(borderColor);
        std::cout << "Border color: (" << int(borderColor.r) << " " << int(borderColor.g) << " " << int(borderColor.b) << " " << int(borderColor.a) << ")" << std::endl;

        Color cellColor = Utils::randColor();
        lvl->setBoardCellBackgroundColor(cellColor);
        std::cout << "Cell color: (" << int(cellColor.r) << " " << int(cellColor.g) << " " << int(cellColor.b) << " " << int(cellColor.a) << ")" << std::endl;

        lvl->centerBoard();
        std::cout << "Centering board" << std::endl;

        // FOOD

        const int minFoodCount = 1;
//        const int maxFoodCount = boardWidth * boardHeight - boundaries.minSnakeSize;
        int foodCount = Utils::randInt(minFoodCount, boundaries.maxFoodCount);
        lvl->setFoodCount(foodCount);
        std::cout << "Food count: " << foodCount << std::endl;

        const int minFoodSize = ((cellSize - borderSize) / 2) / 2;
        const int maxFoodSize = (cellSize - borderSize) / 2;
        int foodSize = Utils::randInt(minFoodSize, maxFoodSize);
        lvl->setFoodSize(foodSize);
        std::cout << "Food size: " << foodSize << std::endl;

        Color foodColor = Utils::randColor();
        lvl->setFoodColor(foodColor);
        std::cout << "Food color: (" << int(foodColor.r) << " " << int(foodColor.g) << " " << int(foodColor.b) << " " << int(foodColor.a) << ")" << std::endl;


        //==========
        // TODO implementation
        lvl->setSnakeStartSize(3);
        lvl->setSnakeStartingPosition(2, 0);
        lvl->setSnakeStartingDirection(RIGHT);
        //==========

        lvl->setSnakeHeadColor(GOLD);
        lvl->setSnakeBodyColor(MAGENTA);

        double levelSpeed = Utils::randInt(8, 20) / 10.0;
        lvl->setLevelSpeed(levelSpeed);
        std::cout << "Level speed: " << levelSpeed << std::endl;

        int minPointsTarget = boardHeight * boardWidth / 2;
        int maxPointsTarget = boardHeight * boardWidth - 5;
        int pointsTarget = Utils::randInt(minPointsTarget, maxPointsTarget);
        lvl->pointsTarget = pointsTarget;
        std::cout << "Points target: " << pointsTarget << std::endl;

        std::cout << "==========================" << std::endl;
        return lvl;
    }
};

#endif //RAYLIB_SNAKE_LEVELGENERATOR_H
