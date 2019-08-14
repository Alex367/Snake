#pragma once
#include <list>
#include "SnakePart.h"

//часть вражеской змейки
class EnemySnakePart :
	public SnakePart
{
public:
	EnemySnakePart(int x, int y);
	~EnemySnakePart();

	static const unsigned char SYMBOL;

	virtual void draw(char **pole);
};

