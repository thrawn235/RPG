#pragma once

#include <glm/vec2.hpp>
using namespace glm;

#include "LazyEngine.h"

class UIObject
{
	protected:
	LazyEngine* Engine;
	vec2 pos;
	int width, height;
	int hirarchy;
	
	public:
	UIObject(LazyEngine* newEngine);
	virtual void Update();
	int GetHirarchy();
	void SetHirarchy(int newHirarchy);
	vec2 GetPos();
	void SetPos(vec2 newPos);
	int GetWidth();
	void SetWidth(int newWidth);
	int GetHeight();
	void SetHeight(int newHeight);
	virtual void Show();
	bool MouseOver();
	bool Clicked();
};

class UIElement : public UIObject
{
	protected:
	public:
	UIElement(LazyEngine* newEngine);
	virtual void Show();
	virtual void Update();
};

class UIContainer : public UIObject
{
	protected:
	public:
	UIContainer(LazyEngine* newEngine);
	virtual void Show();
	virtual void Update();
};
