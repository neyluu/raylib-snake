#include "snake.h"

BodyPart::BodyPart(Vector2 position)
{
    this->position = position;
}

void Snake::init()
{
    body.push_back(BodyPart(Vector2(5, 5)));
    body.push_back(BodyPart(Vector2(5, 4)));
    body.push_back(BodyPart(Vector2(5, 3)));
}

void Snake::draw()
{
    for(int i = body.size() - 1; i >= 0; i--)
    {
        Color color = SKYBLUE;
        if(i == 0) color = GREEN;
        board->drawRectInCell(body[i].position.x, body[i].position.y, 20, 20, color, true, 0, 0);
    }
}
void Snake::update()
{
    if(!isAlive) return;

    checkFood();
    move();
    checkCollisions();
    isHungry = true;
}

void Snake::getEvent()
{
    if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))     moveUp();
    if(IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))  moveRight();
    if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))   moveDown();
    if(IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))   moveLeft();
}

void Snake::reset()
{
    direction = RIGHT;
    isAlive = true;
    isHungry = true;
    points = 0;

    body.clear();
    body.push_back(BodyPart(Vector2(5, 5)));
    body.push_back(BodyPart(Vector2(5, 4)));
    body.push_back(BodyPart(Vector2(5, 3)));

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
    BodyPart oldHead = body.front();
    BodyPart newHead = oldHead;

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
    if(direction == UP || direction == DOWN) return;
    direction = UP;
}
void Snake::moveRight()
{
    if(direction == RIGHT || direction == LEFT) return;
    direction = RIGHT;
}
void Snake::moveDown()
{
    if(direction == UP || direction == DOWN) return;
    direction = DOWN;
}
void Snake::moveLeft()
{
    if(direction == RIGHT || direction == LEFT) return;
    direction = LEFT;
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

bool Snake::alive()
{
    return isAlive;
}
