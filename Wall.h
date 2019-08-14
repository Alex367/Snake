#pragma once
#include "GameObject.h"
class Wall :
	public GameObject
{
public:
	Wall(int x, int y, int lifeTime);
	~Wall();

	static const unsigned char SYMBOL;

	virtual void draw(char **pole);
	
	int lifeTime;
};

