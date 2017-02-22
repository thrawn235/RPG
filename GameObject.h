#pragma once

#include "LazyEngine.h"

class GameObject
{
protected:
	LazyEngine* Engine;
	int PosX;
	int PosY;
public:
	GameObject(LazyEngine* newEngine);
	void Move();
	void Show();
	void Update();
};
