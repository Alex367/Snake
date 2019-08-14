#include "EnemySnakePart.h"

const unsigned char EnemySnakePart::SYMBOL = 'X';

EnemySnakePart::EnemySnakePart(int x, int y) : SnakePart(x, y)
{
}


EnemySnakePart::~EnemySnakePart()
{
}

void EnemySnakePart::draw(char **pole)
{
	pole[y][x] = SYMBOL;
}

