#include "snake.h"

BodyPart::BodyPart(Vector2 position, Direction direction)
{
    this->position = position;
    this->direction = direction;
}

void Snake::init()
{
    body.push_back(BodyPart(Vector2(5, 5), RIGHT));
    body.push_back(BodyPart(Vector2(5, 4), RIGHT));
    body.push_back(BodyPart(Vector2(5, 3), RIGHT));
}

void Snake::draw(double tickRate)
{
    float animationStep = 0;
    if(!isPaused && isAlive && isHungry)
    {
        animationStep = board->getCellSize().y / tickRate * GetFrameTime();
        totalAnimationStep += animationStep;
    }

    for(int i = body.size() - 1; i >= 0; i--)
    {
        int width = 29, height = 29;
        Color color = SKYBLUE;

//        std::cout << "pixel per frame: " << animationStep << std::endl;
//        std::cout << "tickrate: " << tickRate << std::endl;

        // Head
        if(i == 0)
        {
            int offsetX, offsetY;
            color = GREEN;

            if(direction == UP || direction == DOWN)
            {
                width = 29;
                height = 15;
                if(newDirection == UP || newDirection == DOWN) height += int(totalAnimationStep);

                offsetX = (board->getCellSize().x - width) / 2;
                offsetY = direction == UP ? (board->getCellSize().y - height) : 0;
            }
            if(direction == LEFT || direction == RIGHT)
            {
                width = 15;
                height = 29;
                if(newDirection == LEFT || newDirection == RIGHT) width += int(totalAnimationStep);

                offsetX = direction == LEFT ? (board->getCellSize().x - width) : 0;
                offsetY = (board->getCellSize().y - height) / 2;
            }

            board->drawRectInCell(body[i].position.x, body[i].position.y, width, height, color, false, offsetX, offsetY);
        }
        // Tail
        else if(i == body.size() - 1)
        {
            int offsetX, offsetY;

            if(body[i].position.x == body[i - 1].position.x)
            {
                width = 29 - int(totalAnimationStep);
                height = 29;

                if(body[i].position.y > body[i - 1].position.y) offsetX = 0;
                else offsetX = (board->getCellSize().x - width);

                offsetY = (board->getCellSize().y - height) / 2;
            }
            if(body[i].position.y == body[i - 1].position.y)
            {
                width = 29;
                height = 29 - int(totalAnimationStep);

                if(body[i].position.x > body[i - 1].position.x) offsetY = 0;
                else offsetY = (board->getCellSize().y - height);

                offsetX = (board->getCellSize().x - width) / 2;
            }
            board->drawRectInCell(body[i].position.x, body[i].position.y, width, height, color, false, offsetX, offsetY);
        }
        // Body
        else
        {
//            if(body[i].position.y == body[i - 1].position.y && body[i].position.y == body[i + 1].position.y)
//            {
//                width = 20;
//            }
//            if(body[i].position.x == body[i - 1].position.x && body[i].position.x == body[i + 1].position.x)
//            {
//                height = 20;
//            }
            board->drawRectInCell(body[i].position.x, body[i].position.y, width, height, color, true, 0, 0);
        }

    }
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
    direction = newDirection;
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
    if(direction == UP || direction == DOWN) return;
    newDirection = UP;
}
void Snake::moveRight()
{
    if(direction == RIGHT || direction == LEFT) return;
    newDirection = RIGHT;
}
void Snake::moveDown()
{
    if(direction == UP || direction == DOWN) return;
    newDirection = DOWN;
}
void Snake::moveLeft()
{
    if(direction == RIGHT || direction == LEFT) return;
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

bool Snake::alive()
{
    return isAlive;
}
