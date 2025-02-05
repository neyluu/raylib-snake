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
    body.push_back(BodyPart(Vector2(5, 2)));
    body.push_back(BodyPart(Vector2(5, 1)));
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

    move();
    checkCollisions();
}

void Snake::getEvent()
{
    if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) moveUp();
    if(IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) moveRight();
    if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) moveDown();
    if(IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) moveLeft();
}

void Snake::setBoard(Board *board)
{
    this->board = board;
}

void Snake::move()
{
    BodyPart oldHead = body.front();
    BodyPart newHead = oldHead;

    // TODO check for board overflow
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
    body.pop_back();
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
    BodyPart head = body.front();

    for(int i = 1; i < body.size(); i++)
    {
        if(head.position.x == body[i].position.x && head.position.y == body[i].position.y) isAlive = false;
    }
}