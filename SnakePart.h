#pragma once
#include "GameObject.h"

//����� ������
class SnakePart :
	public GameObject
{
public:
	SnakePart(int x, int y);
	~SnakePart();

	static const unsigned char SYMBOL;

	virtual void draw(char **pole);
};

