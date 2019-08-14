#pragma once
#include <list>
#include "SnakePart.h"

class EnemySnake;
class Game;

class Snake
{
public:
	Snake(Game * game, int screenWidth, int screenHeight);
	~Snake();

	std::list<GameObject*> parts;
	int destX;
	int destY;

	virtual void create();
	void update(std::list<GameObject *> *objects, EnemySnake * enemySnake);	//обновление змейки
	void draw(char **rect);			
	void changeDirection(char c);
	

protected:
	Game * game;
	int screenWidth;
	int screenHeight;

	bool checkCollision(std::list<GameObject *> *objects, EnemySnake * enemySnake);

};

