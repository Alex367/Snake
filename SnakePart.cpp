#include "SnakePart.h"

const unsigned char SnakePart::SYMBOL = '0';

SnakePart::SnakePart(int x, int y) : GameObject(x,y)
{
}


SnakePart::~SnakePart()
{
}

void SnakePart::draw(char **pole)
{
	pole[y][x] = SYMBOL;
}
