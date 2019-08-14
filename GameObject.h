#pragma once

//игровой объект, абстрактный родительский класс
class GameObject
{
public:
	GameObject(int x, int y);
	~GameObject();

	int x;
	int y;

	virtual void draw(char **pole) = 0;
};

