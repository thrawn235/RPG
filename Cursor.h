#pragma once

#include "LazyEngine.h"
#include <vector>


class MouseCursor
{
	protected:
	LazyEngine* Engine;
	vec2 Pos;
	
	public:
	MouseCursor(LazyEngine* newEngine);
	void Update();
	void Show();
	vec2 GetPos();
};


class Cursor
{
	protected:
	LazyEngine* Engine;
	MouseCursor* MousePointer;
	vec2 Pos;
	vec2 GridPos;
	bool clicked;
	
	public:
	Cursor(LazyEngine* newEngine);
	void Update();
	void Show();
	vec2 GetPos();
	vec2 GetGridPos();
	void AssignMouse(MouseCursor* newPointer);
};
