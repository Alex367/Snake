#pragma once
#include <list>
#include "Food.h"
#include "Snake.h"
#include "EnemySnake.h"

class Game
{
public:
	Game(int width, int height);
	~Game();
		
	std::list<GameObject*> objects;

	int play();
	void collideObject(std::list<GameObject*>::iterator iter);
	void gameOver();

private:
	Snake *snake;
	EnemySnake * enemySnake;

	int screenWidth;
	int screenHeight;

	char **rect;	
	bool isGameOver;
	int score;		
	int eatenToUpSpeed;
	int delay;	

	void addFood();
	void clearRect();	
	void drawOther();
	void outpRect();
	void updateWalls();
};

