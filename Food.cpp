#include "Food.h"

const unsigned char Food::SYMBOL = 'F';

Food::Food(int x, int y) : GameObject(x, y)
{
}


Food::~Food()
{
}

void Food::draw(char **pole)
{
	pole[y][x] = SYMBOL;
}