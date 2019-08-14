#pragma once
#include "Snake.h"

struct Point
{
	int x;
	int y;
	int G;
	Point *parent;
	Point(int x, int y, Point *parent, int G)
	{
		this->parent = parent;
		this->x = x;
		this->y = y;
		this->G = G;
	}
};

class EnemySnake :
	public Snake
{
public:
	EnemySnake(Game * game, int screenWidth, int screenHeight);
	~EnemySnake();

	virtual void create();
	void update(std::list<GameObject *> *objects, Snake * snake);
private:
	char **pole;

	void ai(std::list<GameObject *> *objects, Snake * snake);	
	void checkCollision(std::list<GameObject *> *objects, Snake * snake);
	void death();
};

