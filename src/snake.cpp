#include "snake.h"

BodyPart::BodyPart(Vector2 position, Direction direction)
{
    this->position = position;
    this->direction = direction;
}


Snake::Snake(Board *board, FoodContainer *foods)
{
    if(board == nullptr)
    {
        LOG(L_ERROR, "Board pointer is NULL")
    }
    if(foods == nullptr)
    {
        LOG(L_ERROR, "Food pointer is NULL")
    }

    this->foods = foods;
}
Snake::Snake(Board *board, FoodContainer *foods, int startSize, int bodyPartWidth, int bodyPartHeight, Color headColor, Color bodyColor)
    : Snake(board, foods)
{
    this->startSize = startSize;
    this->bodyPartWidth = bodyPartWidth;
    this->bodyPartHeight = bodyPartHeight;
    this->headColor = headColor;
    this->bodyColor = bodyColor;
}


void Snake::init()
{
    int borderSize = Board::getCurrent()->getBorderSize();
    bodyPartWidth =  Board::getCurrent()->getCellSize().x - borderSize;
    bodyPartHeight = Board::getCurrent()->getCellSize().y - borderSize;

    // Animations don`t work properly when startSize < 3, maybe can be improved in the future
    if(startSize < 3)
    {
        LOG(L_WARNING, "Start size can`t be less than 3! Start size was set to 3")
        startSize = 3;
    }

    if(!body.empty()) body.clear();

    BodyPart newPart;
    Vector2 newPartPosition;

    for(int i = startSize; i >= 1; i--)
    {
        if(direction == UP)         newPartPosition = { startingPosition.y + startSize - i, startingPosition.x };
        else if(direction == RIGHT) newPartPosition = { startingPosition.y, startingPosition.x - startSize + i };
        else if(direction == DOWN)  newPartPosition = { startingPosition.y - startSize + i, startingPosition.x };
        else if(direction == LEFT)  newPartPosition = { startingPosition.y, startingPosition.x + startSize - i };

        newPart = { newPartPosition, direction };
        body.push_back(newPart);
    }
}
void Snake::draw(double tickRate)
{
    float animationStep = 0;
    if(!isPaused && isAlive && isHungry)
    {
        animationStep = Board::getCurrent()->getCellSize().y / tickRate * GetFrameTime();
        totalAnimationStep += animationStep;
    }

    for(int i = body.size() - 2; i > 0; i--)
    {
        int width = bodyPartWidth;
        int height = bodyPartHeight;
        int offsetX = 0;
        int offsetY = 0;
        int borderSize = Board::getCurrent()->getBorderSize();
        Color color = bodyColor;

        Vector2 topLeft = Board::getCurrent()->getTopLeft();
        Vector2 cellPos = Board::getCurrent()->getCellPosition(body[i].position.x, body[i].position.y);

        // Vertical and horizontal parts are currently unused, can be used late for texture drawing or other fancy shapes
        if(isPartVertical(i))
        {
            offsetY = -borderSize;
            height += borderSize * 2;

            if(isPartPenultimate(i))
            {
                height -= borderSize;
                if(body[i].direction == DOWN) offsetY += borderSize;
            }

            DrawRectangle(topLeft.x + cellPos.x + offsetX, topLeft.y + cellPos.y + offsetY, width, height, bodyColor);
            continue;
        }
        else if(isPartHorizontal(i))
        {
            offsetX = -borderSize;
            width += borderSize * 2;

            if(isPartPenultimate(i))
            {
                width -= borderSize;
                if(body[i].direction == RIGHT) offsetX += borderSize;
            }

            DrawRectangle(topLeft.x + cellPos.x + offsetX, topLeft.y + cellPos.y + offsetY, width, height, bodyColor);
            continue;
        }
        else if(isPartLeftUpCorner(i))
        {
//            color = WHITE;
            if(isPartPenultimate(i)) width -= borderSize;

            DrawRectangle(topLeft.x + cellPos.x + offsetX, topLeft.y + cellPos.y + offsetY, width + borderSize, height, bodyColor);
            if(!isPartPenultimate(i))
            {
                DrawRectangle(topLeft.x + cellPos.x, topLeft.y + cellPos.y + bodyPartHeight, width, borderSize, bodyColor);
            }
        }
        else if(isPartRightUpCorner(i))
        {
//            color = YELLOW;
            if(isPartPenultimate(i))
            {
                width -= borderSize;
                offsetX += borderSize;
            }
            DrawRectangle(topLeft.x + cellPos.x + offsetX - borderSize, topLeft.y + cellPos.y + offsetY, width + borderSize, height, color);
            if(!isPartPenultimate(i))
            {
                DrawRectangle(topLeft.x + cellPos.x, topLeft.y + cellPos.y + bodyPartHeight, width, borderSize, color);
            }
        }
        else if(isPartLeftBottomCorner(i))
        {
//            color = DARKGREEN;
            if(isPartPenultimate(i))
            {
                width -= borderSize;
            }
            DrawRectangle(topLeft.x + cellPos.x + offsetX, topLeft.y + cellPos.y + offsetY, width + borderSize, height, color);
            if(!isPartPenultimate(i))
            {
                DrawRectangle(topLeft.x + cellPos.x, topLeft.y + cellPos.y - borderSize, width, borderSize, color);
            }
        }
        else if(isPartRightBottomCorner(i))
        {
//            color = ORANGE;
            if(isPartPenultimate(i))
            {
                width -= borderSize;
                offsetX += borderSize;
            }
            DrawRectangle(topLeft.x + cellPos.x + offsetX - borderSize, topLeft.y + cellPos.y + offsetY, width + borderSize, height, color);
            if(!isPartPenultimate(i))
            {
                DrawRectangle(topLeft.x + cellPos.x, topLeft.y + cellPos.y - borderSize, width, borderSize, color);
            }
        }
    }

    drawHead();
    drawTail();
}
void Snake::drawHead()
{
    int offsetX = 0;
    int offsetY = 0;
    int width = bodyPartWidth;
    int height = bodyPartHeight;
    int borderSize = Board::getCurrent()->getBorderSize();
    Vector2 topLeft = Board::getCurrent()->getTopLeft();
    Vector2 cellPos = Board::getCurrent()->getCellPosition(body[0].position.x, body[0].position.y);
    Vector2 cellSize = Board::getCurrent()->getCellSize();

    if(direction == UP)
    {
        offsetY = bodyPartHeight - int(totalAnimationStep);
        if(offsetY < cellSize.y - borderSize * 2)
        {
            DrawRectangle(topLeft.x + cellPos.x, topLeft.y + cellPos.y + cellSize.y - borderSize * 2, bodyPartWidth, borderSize, bodyColor);
        }
    }
    else if(direction == DOWN)
    {
        offsetY = int(totalAnimationStep) - cellSize.y + borderSize;
        if(offsetY > -cellSize.y + borderSize * 2)
        {
            DrawRectangle(topLeft.x + cellPos.x, topLeft.y + cellPos.y, bodyPartWidth, borderSize, bodyColor);
        }
    }
    else if(direction == LEFT)
    {
        offsetX = bodyPartWidth - int(totalAnimationStep);
        if(offsetX < cellSize.x - borderSize * 2)
        {
            DrawRectangle(topLeft.x + cellPos.x + cellSize.x - borderSize * 2, topLeft.y + cellPos.y, borderSize, bodyPartHeight, bodyColor);
        }
    }
    else if(direction == RIGHT)
    {
        offsetX = int(totalAnimationStep) - cellSize.x + borderSize;
        if(offsetX > -cellSize.x + borderSize * 2)
        {
            DrawRectangle(topLeft.x + cellPos.x, topLeft.y + cellPos.y, borderSize, bodyPartHeight, bodyColor);
        }
    }

    DrawRectangle(topLeft.x + cellPos.x + offsetX, topLeft.y + cellPos.y + offsetY, width, height, headColor);
}
void Snake::drawTail()
{
    if(!tailAnim) return;

    int offsetX = 0;
    int offsetY = 0;
    int i = body.size() - 1;
    int width = Board::getCurrent()->getCellSize().x;
    int height = Board::getCurrent()->getCellSize().y;
    int borderSize = Board::getCurrent()->getBorderSize();

    if(body[i].position.x == body[i - 1].position.x)
    {
        width -= int(totalAnimationStep);
        if(width < 0) width = 0;

        if(body[i].position.y > body[i - 1].position.y) offsetX = -borderSize;
        else offsetX = Board::getCurrent()->getCellSize().x - width;

        height -= borderSize;
    }
    if(body[i].position.y == body[i - 1].position.y)
    {
        height -= int(totalAnimationStep);
        if(height < 0) height = 0;

        if(body[i].position.x > body[i - 1].position.x) offsetY = -borderSize;
        else offsetY = Board::getCurrent()->getCellSize().y - height;

        width -= borderSize;
    }

    DrawRectangle(  Board::getCurrent()->getTopLeft().x + Board::getCurrent()->getCellPosition(body[i].position.x, body[i].position.y).x + offsetX,
                    Board::getCurrent()->getTopLeft().y + Board::getCurrent()->getCellPosition(body[i].position.x, body[i].position.y).y + offsetY,
                    width,
                    height,
                    bodyColor
                );
}
void Snake::update()
{
    if(!isAlive) return;
    tailAnim = true;

    checkFood();
    move();
    checkCollisions();
    isHungry = true;

    totalAnimationStep = 0;
}
void Snake::getEvent()
{
    if(isPaused) return;

    if(IsKeyPressed(settings.keymap.moveUp)     || IsKeyPressed(KEY_UP))    moveUp();
    if(IsKeyPressed(settings.keymap.moveRight)  || IsKeyPressed(KEY_RIGHT)) moveRight();
    if(IsKeyPressed(settings.keymap.moveDown)   || IsKeyPressed(KEY_DOWN))  moveDown();
    if(IsKeyPressed(settings.keymap.moveLeft)   || IsKeyPressed(KEY_LEFT))  moveLeft();
}
void Snake::reset()
{
    direction = startingDirection;
    newDirection = startingDirection;
    isAlive = true;
    isHungry = true;
    points = 0;
    isPaused = false;

    body.clear();
    init();

    foods->spawnAll();
}


void Snake::setStartSize(int size)
{
    this->startSize = size;
    init();
}
void Snake::setBodyPartSize(int width, int height)
{
    this->bodyPartWidth = width;
    this->bodyPartHeight = height;
}
void Snake::setStartingPosition(Vector2 position)
{
    this->startingPosition = position;
    init();
}
void Snake::setStartingDirection(Direction direction)
{
    this->startingDirection = direction;
    this->direction = direction;
    this->newDirection = direction;
    init();
}
void Snake::setHeadColor(Color color)
{
    this->headColor = color;
}
void Snake::setBodyColor(Color color)
{
    this->bodyColor = color;
}


void Snake::move()
{
    direction = (newDirection != NONE) ? newDirection : direction;
    newDirection = NONE;
    BodyPart oldHead = body.front();
    BodyPart newHead = oldHead;

    newHead.direction = direction;

    if(direction == UP)
    {
        if(newHead.position.x - 1 < 0)
        {
            newHead.position.x = 0;
            isAlive = false;
            return;
        }
        else newHead.position.x--;
    }
    if(direction == RIGHT)
    {
        if(newHead.position.y + 1 >= Board::getCurrent()->getWidth())
        {
            newHead.position.y = Board::getCurrent()->getWidth() - 1;
            isAlive = false;
            return;
        }
        else newHead.position.y++;
    }
    if(direction == DOWN)
    {
        if(newHead.position.x + 1 >= Board::getCurrent()->getHeight())
        {
            newHead.position.x = Board::getCurrent()->getHeight() - 1;
            isAlive = false;
            return;
        }
        else newHead.position.x++;
    }
    if(direction == LEFT)
    {
        if(newHead.position.y - 1 < 0)
        {
            newHead.position.y = 0;
            isAlive = false;
            return;
        }
        else newHead.position.y--;
    }

    body.insert(body.begin(), newHead);
    if(isHungry) body.pop_back();
}
void Snake::moveUp()
{
    if(direction == UP || direction == DOWN || newDirection != NONE) return;
    newDirection = UP;
}
void Snake::moveRight()
{
    if(direction == RIGHT || direction == LEFT || newDirection != NONE) return;
    newDirection = RIGHT;
}
void Snake::moveDown()
{
    if(direction == UP || direction == DOWN || newDirection != NONE) return;
    newDirection = DOWN;
}
void Snake::moveLeft()
{
    if(direction == RIGHT || direction == LEFT || newDirection != NONE) return;
    newDirection = LEFT;
}


void Snake::checkCollisions()
{
    for(int i = 1; i < body.size(); i++)
    {
        if(isHeadInPart(body[i]))
        {
            isAlive = false;
            LOG(L_INFO, "Snake is dead")
            return;
        }
    }
}
void Snake::checkFood()
{
    BodyPart head = body.front();

    if(foods->exist(head.position.x, head.position.y))
    {
        Food *food = foods->getFood(head.position.x, head.position.y);
        isHungry = false;
        tailAnim = false;
        points++;
        if(points > highScore) highScore = points;
        while(isFoodInBody(food)) food->spawn();
    }
}


bool Snake::isHeadInPart(BodyPart part)
{
    BodyPart head = body.front();
    if(head.position.x == part.position.x && head.position.y == part.position.y) return true;
    return false;
}
bool Snake::isFoodInBody(Food *food)
{
    Vector2 foodPos = food->getPosition();
    for(int i = 0; i < body.size(); i++)
    {
        if(foodPos.x == body[i].position.x && foodPos.y == body[i].position.y) return true;
    }
    return false;
}
bool Snake::isPartLeftUpCorner(int i)
{
    return
       (body[i].position.x == body[i - 1].position.x &&
        body[i].position.y == body[i + 1].position.y &&
        body[i].position.y < body[i - 1].position.y &&
        body[i].position.x < body[i + 1].position.x &&
        body[i - 1].direction == RIGHT &&
        body[i + 1].direction != DOWN)
        ||
       (body[i].position.x == body[i + 1].position.x &&
        body[i].position.y == body[i - 1].position.y &&
        body[i].position.y < body[i + 1].position.y &&
        body[i].position.x < body[i - 1].position.x &&
        body[i - 1].direction == DOWN &&
        body[i + 1].direction != RIGHT);
}
bool Snake::isPartRightUpCorner(int i)
{
    return
        (body[i].position.x == body[i + 1].position.x &&
         body[i].position.y == body[i - 1].position.y &&
         body[i].position.y > body[i + 1].position.y &&
         body[i].position.x < body[i - 1].position.x &&
         body[i - 1].direction == DOWN &&
         body[i + 1].direction != LEFT)
         ||
        (body[i].position.x == body[i - 1].position.x &&
         body[i].position.y == body[i + 1].position.y &&
         body[i].position.y > body[i - 1].position.y &&
         body[i].position.x < body[i + 1].position.x &&
         body[i - 1].direction == LEFT &&
         body[i + 1].direction != DOWN);
}
bool Snake::isPartLeftBottomCorner(int i)
{
    return
        (body[i].position.x == body[i - 1].position.x &&
         body[i].position.y == body[i + 1].position.y  &&
         body[i].position.y < body[i - 1].position.y &&
         body[i].position.x > body[i + 1].position.x &&
         body[i - 1].direction == RIGHT &&
         body[i + 1].direction != UP)
         ||
        (body[i].position.x == body[i + 1].position.x &&
         body[i].position.y == body[i - 1].position.y  &&
         body[i].position.y < body[i + 1].position.y &&
         body[i].position.x > body[i - 1].position.x &&
         body[i - 1].direction == UP &&
         body[i + 1].direction != RIGHT);
}
bool Snake::isPartRightBottomCorner(int i)
{
    return
        (body[i].position.x == body[i + 1].position.x &&
         body[i].position.y == body[i - 1].position.y &&
         body[i].position.y > body[i + 1].position.y &&
         body[i].position.x > body[i - 1].position.x &&
         body[i - 1].direction == UP &&
         body[i + 1].direction != LEFT)
         ||
        (body[i].position.x == body[i - 1].position.x &&
         body[i].position.y == body[i + 1].position.y &&
         body[i].position.y > body[i - 1].position.y &&
         body[i].position.x > body[i + 1].position.x &&
         body[i - 1].direction == LEFT &&
         body[i + 1].direction != UP);
}
bool Snake::isPartVertical(int i)
{
    return body[i].position.y == body[i - 1].position.y && body[i].position.y == body[i + 1].position.y;
}
bool Snake::isPartHorizontal(int i)
{
    return body[i].position.x == body[i - 1].position.x && body[i].position.x == body[i + 1].position.x;
}
bool Snake::isPartPenultimate(int i)
{
    return i + 1 == body.size() - 1;
}

bool Snake::alive() const {
    return isAlive;
}
