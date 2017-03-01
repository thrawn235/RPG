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
	bool visible;
	bool spanHorizontal, spanVertical;
	int timeLastClicked;
	
	public:
	UIObject(LazyEngine* newEngine);
	int GetHirarchy();
	void SetHirarchy(int newHirarchy);
	vec2 GetPos();
	void SetPos(vec2 newPos);
	int GetWidth();
	void SetWidth(int newWidth);
	int GetHeight();
	void SetHeight(int newHeight);
	bool GetVisible();
	void SetVisible(bool newVisible);
	bool GetSpanHorizontal();
	void SetSpanHorizontal(bool newSpanHorizontal);
	bool GetSpanVertical();
	void SetSpanVertical(bool newSpanVertical);
	
	virtual vec2 GetUsableAreaPos(UIObject* Caller);
	virtual int GetUsableAreaWidth(UIObject* Caller);
	virtual int GetUsableAreaHeight(UIObject* Caller);
	virtual void Update();
	virtual void Show();
	bool MouseOver();
	bool Clicked();
};

class UIElement : public UIObject
{
	protected:
	UIObject* parent;
	
	public:
	UIObject* GetParent();
	void SetParent(UIObject* newParent);
	
	UIElement(LazyEngine* newEngine);
	virtual void Show();
	virtual void Update();
};

class UIContainer : public UIObject
{
	protected:
	UIElement *child;
	
	public:
	UIContainer(LazyEngine* newEngine);
	virtual vec2 GetUsableAreaPos(UIObject* Caller);
	virtual int GetUsableAreaWidth(UIObject* Caller);
	virtual int GetUsableAreaHeight(UIObject* Caller);
	virtual void SetChild(UIElement* newChild);
	virtual void Show();
	virtual void Update();
};


#include <SDL2/SDL.h>
