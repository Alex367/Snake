#include "EnemySnake.h"
#include "EnemySnakePart.h"
#include "Food.h"
#include <vector>

EnemySnake::EnemySnake(Game * game, int screenWidth, int screenHeight) : Snake(game, screenWidth, screenHeight)
{
	pole = new char*[screenHeight];
	for (int i = 0; i < screenHeight; i++)
	{
		pole[i] = new char[screenWidth];
	}
}


EnemySnake::~EnemySnake()
{
	for (int i = 0; i < screenHeight; i++)
		delete[] pole[i];

	delete[] pole;
}

void EnemySnake::create()
{
	int x = screenWidth - 10;
	int y = screenHeight / 3 * 2;

	int size = 3;

	destX = -1;
	destY = 0;

	for (int i = 0; i < size; i++)
	{
		parts.push_back(new EnemySnakePart(x, y));
		x--;
	}
}

void EnemySnake::update(std::list<GameObject *> *objects, Snake * snake)
{
	ai(objects, snake);

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

	parts.push_back(new EnemySnakePart(newX, newY));

	checkCollision(objects, snake);
}

void EnemySnake::ai(std::list<GameObject *> *objects, Snake * snake)
{	
	GameObject *head = parts.back();

	//ищем ближайшую еду
	int minDist = -1;
	GameObject *food = NULL;
	for (auto iter = objects->begin(); iter != objects->end(); iter++)
	{
		int dist = abs((*iter)->x - head->x) + abs((*iter)->y - head->y);
		if (minDist == -1 || minDist > dist)
			food = *iter;
	}

	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
			pole[i][j] = 0;
	}

	//на матрице 0 - пустая клетка
	//			 1 - еда
	//			 2 - непроходимая часть

	//наносим на матрицу стены и еду
	for (auto iter = objects->begin(); iter != objects->end(); iter++)
	{
		if (dynamic_cast<Food*>(*iter))
			pole[(*iter)->y][(*iter)->x] = 1;
		else
			pole[(*iter)->y][(*iter)->x] = 2;
	}

	for (auto iter = parts.begin(); iter != parts.end(); iter++)
		pole[(*iter)->y][(*iter)->x] = 2;

	for (auto iter = snake->parts.begin(); iter != snake->parts.end(); iter++)
		pole[(*iter)->y][(*iter)->x] = 2;

	std::list<Point*> openList;	
	std::vector<Point*> closeList;	  

	openList.push_back(new Point(head->x, head->y, NULL, 0));

	Point * finStep = NULL;	//рассматриваемый элемент

	do
	{
		Point *nowPoint = NULL;
		int minF = -1;
		for (auto iter = openList.begin(); iter != openList.end(); iter++)
		{
			//вычисляем F
			int f = abs(food->x - (*iter)->x) + abs(food->y - (*iter)->y) + (*iter)->G;
			//находим минимальный
			if (minF == -1 || minF > f)
			{
				minF = f;
				nowPoint = *iter;
			}
		}

		if (nowPoint==NULL)
			break;

		for (int i = -1; i <= 1; i ++)
		{
			for (int j = -1; j <= 1; j ++)
			{
				if (i!=0 && j!=0 || i==0 && j==0)
					continue;

				int newX = nowPoint->x + j;
				int newY = nowPoint->y + i;

				if (newX < 0 || newX >= screenWidth ||
					newY < 0 || newY >= screenHeight ||
					pole[newY][newX] == 2)
					continue;

				bool fnd = false;
				for (auto iter = openList.begin(); iter != openList.end(); iter++)
					if ((*iter)->x == newX && (*iter)->y == newY)
					{
						fnd = true;
						break;
					}

				if (!fnd)
					for (auto iter = closeList.begin(); iter != closeList.end(); iter++)
						if ((*iter)->x == newX && (*iter)->y == newY)
						{
							fnd = true;
							break;
						}

				if (!fnd)
				{
					openList.push_back(new Point(newX, newY, nowPoint, nowPoint->G + 10));

					if (pole[newY][newX] == 1)
					{
						//помечаем как конец маршрута
						finStep = openList.back();
						break;
					}
				}
			}

			if (finStep)
				break;
		}

		closeList.push_back(nowPoint);
		//добавляем в открытый список
		openList.pop_front();
	} while (!finStep);
	
	if (finStep)
	{
		Point *p = finStep;
		
		while (p->parent->parent != NULL)
			p = p->parent;

		destX = p->x - head->x;
		destY = p->y - head->y;

		if (destX < -1)
			destX = -1;
		if (destY < -1)
			destY = -1;
		if (destX > 1)
			destX = 1;
		if (destY > 1)
			destY = 1;

		if (destX != 0 && destY != 0)
			destY = 0;
	}
}

void EnemySnake::checkCollision(std::list<GameObject *> *objects, Snake * snake)
{
	GameObject *head = parts.back();


	bool eat = false;
	for (auto iter = objects->begin(); iter != objects->end(); iter++)
	{
		if ((*iter)->x == head->x && (*iter)->y == head->y)
		{
			eat = true;
			objects->erase(iter);
			break;
		}
	}
	
	if (!eat)
		parts.pop_front();

	auto lastIter = parts.end();
	lastIter--;

	for (auto iter = parts.begin(); iter != lastIter; iter++)
	{
		if ((*iter)->x == head->x && (*iter)->y == head->y)
		{
			death();
			break;
		}
	}

	for (auto iter = snake->parts.begin(); iter != snake->parts.end(); iter++)
	{
		if ((*iter)->x == head->x && (*iter)->y == head->y)
		{
			death();
			break;
		}
	}

}

void EnemySnake::death()
{
	parts.clear();

	int x = screenWidth - 1;
	int y = screenHeight + 3;
	int size = 3;

	destX = 0;
	destY = -1;

	for (int i = 0; i < size; i++)
	{
		parts.push_back(new EnemySnakePart(x, y));
		y--;
	}
}