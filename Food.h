#pragma once
#include "GameObject.h"

//��� ��� �����
class Food :
	public GameObject
{
public:
	Food(int x, int y);
	~Food();

	static const unsigned char SYMBOL;

	virtual void draw(char **pole);
};

