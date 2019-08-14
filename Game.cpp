#include "Game.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
#include "Wall.h"
#include "EnemySnakePart.h"
#include "windows.h"

Game::Game(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	isGameOver = false;

	rect = new char*[screenHeight];
	for (int i = 0; i < screenHeight; i++)
		rect[i] = new char[screenWidth];

	snake = new Snake(this, screenWidth, screenHeight);
	snake->create();
	enemySnake = new EnemySnake(this, screenWidth, screenHeight);
	enemySnake->create();

	score = 0;
	eatenToUpSpeed = 0;
	delay = 500;	

	addFood();
}


Game::~Game()
{
	for (int i = 0; i < screenHeight; i++)
		delete[] rect[i];

	delete rect;
}

int Game::play()
{
	while (!isGameOver)
	{
		clearRect();	

		unsigned char c;
		if (kbhit())
		{		
			unsigned char c = getch();

			if (c == 224)  
			{
				c = getch();
				snake->changeDirection(c);
			}
		}

		int cntFood = 0;
		int cntOther = 0;
		for (auto iter = objects.begin(); iter != objects.end(); iter++)
		{
			if (dynamic_cast<Food*>(*iter) != NULL)
				cntFood++;
			else
				cntOther++;
		}

		if (cntFood< 10)
			addFood();

		updateWalls();

		snake->update(&objects, enemySnake);
		snake->draw(rect);

		enemySnake->update(&objects, snake);
		enemySnake->draw(rect);

		drawOther();
				
		outpRect();

		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}

	return score;
}

void Game::clearRect()
{
	for (int i = 0; i < screenHeight; i++)
		for (int j = 0; j < screenWidth; j++)
			rect[i][j] = ' ';
}

void Game::collideObject(std::list<GameObject*>::iterator iter)
{
	if (dynamic_cast<Food*>(*iter) != NULL)
	{
		score++;
		eatenToUpSpeed++;

		if (eatenToUpSpeed >= 5)
		{ 
			eatenToUpSpeed = 0;
			delay -= 10;
			if (delay < 100)
				delay = 100;
		}

		objects.erase(iter);
	}
	
}

void Game::addFood()
{
	bool collision = false;

	int sx = rand() % screenWidth;
	int sy = rand() % screenHeight;

	int x = sx;
	int y = sy;

	do 
	{
		collision = false;

		//проверка на пересечение со змейкой
		for (auto iter = snake->parts.begin(); iter != snake->parts.end(); iter++)
		{
			if ((*iter)->x == x && (*iter)->y == y)
			{
				collision = true;
				break;
			}
		}

		if (!collision)
		{
			//проверка на пересечение со змейкой компьютера
			for (auto iter = enemySnake->parts.begin(); iter != enemySnake->parts.end(); iter++)
			{
				if ((*iter)->x == x && (*iter)->y == y)
				{
					collision = true;
					break;
				}
			}
		}
		
		if (!collision)
		{
			//проверка на пересечение с остальными объектами
			for (auto iter = objects.begin(); iter != objects.end(); iter++)
			{
				if ((*iter)->x == x && (*iter)->y == y)
				{
					collision = true;
					break;
				}
			}
		}

		if (collision)
		{
			x++; 
			if (x >= screenWidth) 
			{
				x = 0;
				y++;
				if (y >= screenHeight)
					y = 0;
			}
			if (x == sx && y == sy)
				break;
		}

	} while (collision);

	if (!collision)
	{
		objects.push_back(new Food(x, y));
	}
}
void Game::outpRect()
{
	system("CLS");	//очистка
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	std::cout << "Scores: " << score << std::endl;

	unsigned char wallThrough = 176;
	
	for (int j = 0; j <= screenWidth+1; j++)
		std::cout << wallThrough;

	std::cout << std::endl;

	for (int i = 0; i < screenHeight; i++)
	{
		//левая часть рамки
		std::cout << wallThrough;

		for (int j = 0; j < screenWidth; j++)
		{
			if (rect[i][j] == SnakePart::SYMBOL)
				SetConsoleTextAttribute(hConsole, 10);
			else if (rect[i][j] == EnemySnakePart::SYMBOL)
				SetConsoleTextAttribute(hConsole, 4);
			else if (rect[i][j] == Food::SYMBOL)
				SetConsoleTextAttribute(hConsole, 6);
			else
				SetConsoleTextAttribute(hConsole, 7);
			
			std::cout << rect[i][j];
		}
		//правая часть рамки
		std::cout << wallThrough;

		std::cout << std::endl;
	}
	for (int j = 0; j <= screenWidth+1; j++)
		std::cout << wallThrough;
}

void Game::drawOther()
{
	for (auto iter = objects.begin(); iter != objects.end(); iter++)
		(*iter)->draw(rect);
}

void Game::gameOver()
{
	isGameOver = true;
}

void Game::updateWalls()
{
	int cntWall = 0;
	for (auto iter = objects.begin(); iter != objects.end(); )
	{
		Wall *wall = dynamic_cast<Wall*>(*iter);
		if (wall != NULL)
		{
			if (wall->lifeTime <= 0)
			{
				iter = objects.erase(iter);
				continue;
			}
			else
				cntWall++;
		}

		iter++;
	}
	const int sizeX = 3;
	const int sizeY = 2;

	if (cntWall < 6 * 10)
	{
		for (int i = 0; i < 5; i++)
		{
			bool collision = false;
			//случайные координаты блока
			int x = rand() % (screenWidth -3);
			int y = rand() % (screenHeight-2);

			for (int dy = 0; dy < sizeY; dy++)
			{
				for (int dx = 0; dx < sizeX; dx++)
				{
					for (auto iter = snake->parts.begin(); iter != snake->parts.end(); iter++)
					{
						if ((*iter)->x == x + dx && (*iter)->y == y + dy)
						{
							collision = true;
							break;
						}
					}

					if (collision) 
						break;

					for (auto iter = enemySnake->parts.begin(); iter != enemySnake->parts.end(); iter++)
					{
						if ((*iter)->x == x + dx && (*iter)->y == y + dy)
						{
							collision = true;
							break;
						}
					}

					if (collision) 
						break;

					for (auto iter = objects.begin(); iter != objects.end(); iter++)
					{
						if ((*iter)->x == x + dx && (*iter)->y == y + dy)
						{
							collision = true;
							break;
						}
					}

				}

				if (collision)
					break;
			}
			
			if (!collision)
			{
				int time = rand() % 200;
				for (int dy = 0; dy < sizeY; dy++)
					for (int dx = 0; dx < sizeX; dx++)
					{
						objects.push_back(new Wall(x+dx, y+dy, time));
					}
			}
		}
	}
}