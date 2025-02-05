#include "snake.h"

BodyPart::BodyPart(Vector2 position)
{
    this->position = position;
}

void Snake::init()
{
    body.push_back(BodyPart(Vector2(5, 5)));
    body.push_back(BodyPart(Vector2(5, 4)));
}

void Snake::draw()
{
    for(int i = 0; i < body.size(); i++)
    {
        Color color = SKYBLUE;
        if(i == 0) color = GREEN;
        board->drawRectInCell(body[i].position.x, body[i].position.y, 20, 20, color, true, 0, 0);
    }
}
void Snake::update()
{
    move();
}

void Snake::getEvent()
{
    if(IsKeyPressed(KEY_W)) moveUp();
    if(IsKeyPressed(KEY_D)) moveRight();
    if(IsKeyPressed(KEY_S)) moveDown();
    if(IsKeyPressed(KEY_A)) moveLeft();
    std::cout << "dir: " << direction << std::endl;
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
    if(direction == UP) newHead.position.x--;
    if(direction == RIGHT) newHead.position.y++;
    if(direction == DOWN) newHead.position.x++;
    if(direction == LEFT) newHead.position.y--;

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