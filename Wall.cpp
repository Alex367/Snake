#include "Wall.h"

const unsigned char Wall::SYMBOL = 219;

Wall::Wall(int x, int y, int lifeTime) : GameObject(x, y)
{
	this->lifeTime = lifeTime;
}


Wall::~Wall()
{
}

void Wall::draw(char **pole)
{
	lifeTime--;
	pole[y][x] = SYMBOL;
}