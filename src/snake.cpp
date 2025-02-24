#include "snake.h"

BodyPart::BodyPart(Vector2 position, Direction direction)
{
    this->position = position;
    this->direction = direction;
}

Snake::Snake(Board *board, Food *food)
{
    if(board == nullptr)
    {
        std::cout << "ERROR [ SNAKE ] : board pointer is NULL!" << std::endl;
    }
    if(food == nullptr)
    {
        std::cout << "ERROR [ SNAKE ] : food pointer is NULL!" << std::endl;
    }

    this->board = board;
    this->food = food;
}
Snake::Snake(Board *board, Food *food, int startSize, int bodyPartWidth, int bodyPartHeight, Color headColor, Color bodyColor)
    : Snake(board, food)
{
    this->startSize = startSize;
    this->bodyPartWidth = bodyPartWidth;
    this->bodyPartHeight = bodyPartHeight;
    this->headColor = headColor;
    this->bodyColor = bodyColor;
}

void Snake::init()
{
    int borderSize = board->getBorderSize();
    bodyPartWidth = board->getCellSize().x - borderSize;
    bodyPartHeight = board->getCellSize().y - borderSize;

    // Animations don`t work properly when startSize < 3, maybe can be improved in the future
    if(startSize < 3)
    {
        std::cout << "WARNING: Start size can`t be less than 3! Start size was set to 3" << std::endl;
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
        animationStep = board->getCellSize().y / tickRate * GetFrameTime();
        totalAnimationStep += animationStep;
    }

    for(int i = body.size() - 2; i > 0; i--)
    {
        int width = bodyPartWidth;
        int height = bodyPartHeight;
        int offsetX = 0;
        int offsetY = 0;
        int borderSize = board->getBorderSize();
        Color color = bodyColor;

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

            board->drawRectInCell(body[i].position.x, body[i].position.y, width, height, bodyColor, false, offsetX , offsetY);
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

            board->drawRectInCell(body[i].position.x, body[i].position.y, width, height, bodyColor  , false, offsetX, offsetY);
            continue;
        }
        else if(isPartLeftUpCorner(i))
        {
//            color = WHITE;
            if(isPartPenultimate(i)) width -= borderSize;

            board->drawRectInCell(body[i].position.x, body[i].position.y, width + borderSize, height, color, false, 0, 0);
            if(!isPartPenultimate(i))
            {
                board->drawRectInCell(body[i].position.x, body[i].position.y, width, borderSize, color, false, 0, bodyPartHeight);
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
            board->drawRectInCell(body[i].position.x, body[i].position.y, width + borderSize, height, color, false, -borderSize + offsetX, 0);
            if(!isPartPenultimate(i))
            {
                board->drawRectInCell(body[i].position.x, body[i].position.y, width, borderSize, color, false, 0, bodyPartHeight);
            }
        }
        else if(isPartLeftBottomCorner(i))
        {
//            color = DARKGREEN;
            if(isPartPenultimate(i))
            {
                width -= borderSize;
            }
            board->drawRectInCell(body[i].position.x, body[i].position.y, width + borderSize, height, color, false, 0, 0);
            if(!isPartPenultimate(i))
            {
                board->drawRectInCell(body[i].position.x, body[i].position.y, width, borderSize, color, false, 0, -borderSize);
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
            board->drawRectInCell(body[i].position.x, body[i].position.y, width + borderSize, height, color, false, -borderSize + offsetX, 0);
            if(!isPartPenultimate(i))
            {
                board->drawRectInCell(body[i].position.x, body[i].position.y, width, borderSize, color, false, 0, -borderSize);
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
    int borderSize = board->getBorderSize();

    //debug
//    board->drawRectInCell(body[0].position.x, body[0].position.y, width, height, BLUE, false, 0, 0);

    if(direction == UP)
    {
        offsetY = bodyPartHeight - int(totalAnimationStep);
        if(offsetY < board->getCellSize().y - borderSize * 2)
        {
            board->drawRectInCell(body[0].position.x, body[0].position.y, bodyPartWidth, borderSize, bodyColor, false, 0, board->getCellSize().y - borderSize * 2);
        }
    }
    else if(direction == DOWN)
    {
        offsetY = int(totalAnimationStep) - board->getCellSize().y + borderSize;
        if(offsetY > -board->getCellSize().y + borderSize * 2)
        {
            board->drawRectInCell(body[0].position.x, body[0].position.y, bodyPartWidth, borderSize, bodyColor, false, 0,0);
        }
    }
    else if(direction == LEFT)
    {
        offsetX = bodyPartWidth - int(totalAnimationStep);
        if(offsetX < board->getCellSize().x - borderSize * 2)
        {
            board->drawRectInCell(body[0].position.x, body[0].position.y, borderSize, bodyPartHeight, bodyColor, false, board->getCellSize().x - borderSize * 2, 0);
        }
    }
    else if(direction == RIGHT)
    {
        offsetX = int(totalAnimationStep) - board->getCellSize().x + borderSize;
        if(offsetX > -board->getCellSize().x + borderSize * 2)
        {
            board->drawRectInCell(body[0].position.x, body[0].position.y, borderSize, bodyPartHeight, bodyColor, false, 0, 0);
        }
    }

    board->drawRectInCell(body[0].position.x, body[0].position.y, width, height, headColor, false, offsetX, offsetY);
}
void Snake::drawTail()
{
    if(!tailAnim) return;

    int offsetX = 0;
    int offsetY = 0;
    int i = body.size() - 1;
    int width = board->getCellSize().x;
    int height = board->getCellSize().y;
    int borderSize = board->getBorderSize();

    //debug
    board->drawRectInCell(body[i].position.x, body[i].position.y, width, height, BLUE, false, 0, 0);

    if(body[i].position.x == body[i - 1].position.x)
    {
        width -= int(totalAnimationStep);
        if(width < 0) width = 0;

        if(body[i].position.y > body[i - 1].position.y) offsetX = -borderSize;
        else offsetX = board->getCellSize().x - width;

        height -= borderSize;
    }
    if(body[i].position.y == body[i - 1].position.y)
    {
        height -= int(totalAnimationStep);
        if(height < 0) height = 0;

        if(body[i].position.x > body[i - 1].position.x) offsetY = -borderSize;
        else offsetY = board->getCellSize().y - height;

        width -= borderSize;
    }

    board->drawRectInCell(body[i].position.x, body[i].position.y, width, height, bodyColor, false, offsetX, offsetY);
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

    food->spawn();
}

void Snake::setBoard(Board *board)
{
    this->board = board;
}
void Snake::setFood(Food *food)
{
    this->food = food;
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
        if(newHead.position.y + 1 >= board->getWidth())
        {
            newHead.position.y = board->getWidth() - 1;
            isAlive = false;
            return;
        }
        else newHead.position.y++;
    }
    if(direction == DOWN)
    {
        if(newHead.position.x + 1 >= board->getHeight())
        {
            newHead.position.x = board->getHeight() - 1;
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
            std::cout << "DEAD\n";
            return;
        }
    }
}
void Snake::checkFood()
{
    BodyPart head = body.front();
    Vector2 foodPos = food->getPosition();

    if(head.position.x == foodPos.x && head.position.y == foodPos.y)
    {
        isHungry = false;
        tailAnim = false;
        points++;
        if(points > highScore) highScore = points;
        while(isFoodInBody()) food->spawn();
    }
}

bool Snake::isHeadInPart(BodyPart part)
{
    BodyPart head = body.front();
    if(head.position.x == part.position.x && head.position.y == part.position.y) return true;
    return false;
}
bool Snake::isFoodInBody()
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

bool Snake::alive()
{
    return isAlive;
}
