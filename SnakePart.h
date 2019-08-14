#pragma once
#include "GameObject.h"

//часть змейки
class SnakePart :
	public GameObject
{
public:
	SnakePart(int x, int y);
	~SnakePart();

	static const unsigned char SYMBOL;

	virtual void draw(char **pole);
};

