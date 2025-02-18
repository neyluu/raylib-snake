#include "snake.h"

BodyPart::BodyPart(Vector2 position, Direction direction)
{
    this->position = position;
    this->direction = direction;
}

void Snake::init()
{
    body.push_back(BodyPart(Vector2(5, 6), RIGHT));
    body.push_back(BodyPart(Vector2(5, 5), RIGHT));
    body.push_back(BodyPart(Vector2(5, 4), RIGHT));
    body.push_back(BodyPart(Vector2(5, 3), RIGHT));
    body.push_back(BodyPart(Vector2(5, 2), RIGHT));
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
        int width = 28;
        int height = 28;
        int offsetX, offsetY;
        Color color = SKYBLUE;

        // Vertical and horizontal parts are currently unused, can be used late for texture drawing or other fancy shapes
        if(isPartVertical(i))
        {
            height += 4;
            // offsetY = 4;
            board->drawRectInCell(body[i].position.x, body[i].position.y, width, height, bodyColor, true, 0, 0);
            continue;
        }
        else if(isPartHorizontal(i))
        {
            width += 4;
            // offsetX = 4;
            board->drawRectInCell(body[i].position.x, body[i].position.y, width, height, bodyColor  , true, 0, 0);
            continue;
        }
        else if(isPartLeftUpCorner(i))
        {
            // color = WHITE;
            offsetX = 1;
            offsetY = 1;
            board->drawRectInCell(body[i].position.x, body[i].position.y, width, 1, color, false, 1, board->getCellSize().y - 1);
        }
        else if(isPartRightUpCorner(i))
        {
            // color = YELLOW;
            offsetX = 0;
            offsetY = 1;
            board->drawRectInCell(body[i].position.x, body[i].position.y, width, 1, color, false, 1, board->getCellSize().y - 1);
        }
        else if(isPartLeftBottomCorner(i))
        {
            // color = DARKGREEN;
            offsetX = 1;
            offsetY = 1;
            board->drawRectInCell(body[i].position.x, body[i].position.y, width, 1, color, false, 1, 0);
        }
        else if(isPartRightBottomCorner(i))
        {
            // color = ORANGE;
            offsetX = 0;
            offsetY = 1;
            board->drawRectInCell(body[i].position.x, body[i].position.y, width, 1, color, false, 1, 0);
        }

        board->drawRectInCell(body[i].position.x, body[i].position.y, width + 1, height, color, false, offsetX, offsetY);
    }

    drawHead();
    drawTail();
}
void Snake::drawHead()
{
    int offsetX, offsetY;

    if(direction == UP || direction == DOWN)
    {
        offsetX = (board->getCellSize().x - bodyPartWidth) / 2;

        if(direction == UP) offsetY = bodyPartHeight - int(totalAnimationStep);
        if(direction == DOWN) offsetY = int(totalAnimationStep) - board->getCellSize().y;
    }
    if(direction == LEFT || direction == RIGHT)
    {
        offsetY = (board->getCellSize().y - bodyPartHeight) / 2;

        if(direction == LEFT) offsetX = bodyPartWidth - int(totalAnimationStep);
        if(direction == RIGHT) offsetX = int(totalAnimationStep) - board->getCellSize().x;
    }

    board->drawRectInCell(body[0].position.x, body[0].position.y, bodyPartWidth, bodyPartHeight, headColor, false, offsetX, offsetY);
}
void Snake::drawTail()
{
    int offsetX, offsetY;
    int i = body.size() - 1;
    int width = bodyPartWidth;
    int height = bodyPartHeight;

    if(body[i].position.x == body[i - 1].position.x)
    {
        width -= int(totalAnimationStep);

        if(body[i].position.y > body[i - 1].position.y) offsetX = -2;
        else offsetX = (board->getCellSize().x - width) + 2;

        offsetY = (board->getCellSize().y - height) / 2;
    }
    if(body[i].position.y == body[i - 1].position.y)
    {
        height -= int(totalAnimationStep);

        if(body[i].position.x > body[i - 1].position.x) offsetY = -2;
        else offsetY = (board->getCellSize().y - height) + 2;

        offsetX = (board->getCellSize().x - width) / 2;
    }
    board->drawRectInCell(body[i].position.x, body[i].position.y, width, height, bodyColor, false, offsetX, offsetY);
}

void Snake::update()
{
    if(!isAlive) return;

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
direction = RIGHT;
isAlive = true;
isHungry = true;
points = 0;
isPaused = false;

body.clear();
body.push_back(BodyPart(Vector2(5, 5), RIGHT));
body.push_back(BodyPart(Vector2(5, 4), RIGHT));
body.push_back(BodyPart(Vector2(5, 3), RIGHT));

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

void Snake::move()
{
    direction = newDirection != NONE ? newDirection : direction;
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
        if(newHead.position.y + 1 >= board->getHeight())
        {
            newHead.position.y = board->getHeight() - 1;
            isAlive = false;
            return;
        }
        else newHead.position.y++;
    }
    if(direction == DOWN)
    {
        if(newHead.position.x + 1 >= board->getWidth())
        {
            newHead.position.x = board->getWidth() - 1;
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

bool Snake::alive()
{
    return isAlive;
}
