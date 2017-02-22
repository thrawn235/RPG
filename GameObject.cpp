#include "GameObject.h"

GameObject::GameObject(LazyEngine* newEngine)
{
	PosX = 0;
	PosY = 0;
	Engine = newEngine;
}

void GameObject::Move()
{
	PosX++;
}

void GameObject::Show()
{
	Engine->Graphics->DrawSprite("Heroes", PosX, PosY, 25);
}

void GameObject::Update()
{
	Move();
	Show();
}
