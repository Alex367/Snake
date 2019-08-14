#include "Snake.h"
#include "Game.h"
#include "EnemySnake.h"

Snake::Snake(Game * game, int screenWidth, int screenHeight)
{
	this->game = game;
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;

}


Snake::~Snake()
{
	for (auto iter = parts.begin(); iter != parts.end(); iter++)
		delete *iter;
}

void Snake::create()
{
	int x = 10;
	int y = screenHeight / 3;
	int size = 3;

	destX = 1;
	destY = 0;

	for (int i = 0; i < size; i++)
	{
		parts.push_back(new SnakePart(x, y));
		x++;
	}
}

void Snake::update(std::list<GameObject *> *objects, EnemySnake * enemySnake)
{
	GameObject *head = parts.back();

	int newX = head->x + destX;
	int newY = head->y + destY;

	if (newX < 0)
		newX = screenWidth - 1;

	if (newY < 0)
		newY = screenHeight - 1;

	if (newX >= screenWidth)
		newX = 0;

	if (newY >= screenHeight)
		newY = 0;		

	parts.push_back(new SnakePart(newX, newY));

	if (!checkCollision(objects, enemySnake))
		parts.pop_front();
}

void Snake::draw(char **rect)
{
	for (auto iter = parts.begin(); iter != parts.end(); iter++)
		(*iter)->draw(rect);
}

bool Snake::checkCollision(std::list<GameObject *> *objects, EnemySnake * enemySnake)
{
	GameObject *head = parts.back();

	auto lastIter = parts.end();
	lastIter--;

	for (auto iter = parts.begin(); iter != lastIter; iter++)
	{
		if ((*iter)->x == head->x && (*iter)->y == head->y)
		{
			game->gameOver();
			return false;
		}
	}

	for (auto iter = enemySnake->parts.begin(); iter != enemySnake->parts.end(); iter++)
	{
		if ((*iter)->x == head->x && (*iter)->y == head->y)
		{
			game->gameOver();
			return false;
		}
	}

	for (auto iter = objects->begin(); iter != objects->end(); iter++)
	{
		if ((*iter)->x == head->x && (*iter)->y == head->y)
		{
			if (dynamic_cast<Food*>(*iter)) 
			{
				game->collideObject(iter);
				return true;
			}
			else
			{
				game->gameOver();
				return false;
			}			
		}
	}


	return false;
}

//измеенение направления движения
void Snake::changeDirection(char c)
{
	switch (c)
	{
	case 72:
		// стрелка вверх
		if (destX != 0) //проверяем можно ли повернуть вверх, можно только из горизонтального положения
		{
			destY = -1;
			destX = 0;
		}
		
		break;
	case 80:
		// стрелка вниз

		if (destX != 0) //проверяем можно ли повернуть вниз, можно только из горизонтального положения
		{
			destY = 1;
			destX = 0;
		}

		break;
	case 77:
		// стрелка вправо

		if (destY != 0) //проверяем можно ли повернуть вправо, можно только из вертикального положения
		{
			destY = 0;
			destX = 1;
		}
		break;
	case 75:
		// стрелка влево

		if (destY != 0)  //проверяем можно ли повернуть влево, можно только из вертикального положения
		{
			destY = 0;
			destX = -1;
		}

		break;
	}
}