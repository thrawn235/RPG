#pragma once

#include <iostream>
#include <glm/vec2.hpp>

using namespace std;
using namespace glm;

#include "LazyEngine.h"

class MenuHandler;

class UIElement
{
	protected:
	LazyEngine* Engine;
	MenuHandler* Menu;
	vec2 pos;
	int width;
	int height;
	bool spanHorizontal;
	bool spanVertical;
	bool active; //visible and interactable
	bool focus;
	UIElement* ParentElement;
	SDL_Color BorderColor;
	SDL_Color BackgroundColor;
	int lastInputTime;
	int inputCoolDown;
	UIElement* LinkedElement;
	UIElement* LinkParent;
	int Hirarchy;
	
	public:
	UIElement(LazyEngine* newEngine);
	UIElement(MenuHandler* newHandler);
	virtual void Update();
	virtual void Show();
	virtual bool MouseOver();
	virtual bool IsActive();
	virtual bool HasFocus();
	virtual void SetSpanHorizontal(bool newSpanHorizontal);
	virtual void SetSpanVertical(bool newSpanVertical);
	virtual bool HasParent();
	virtual bool HasChildren();
	virtual bool CheckChildrenForFocus();
	virtual void SetBorderColor(int R, int G, int B, int A);
	virtual void SetBackgroundColor(int R, int G, int B, int A);
	virtual bool Clicked();
	virtual bool CoolingDown();
	virtual void SetActive(bool newActive);
	virtual void SetFocus(bool newFocus);
	virtual void SetPosToMousePos();
	virtual void SetPos(vec2 newPos);
	virtual vec2 GetPos();
	virtual int GetWidth();
	virtual int GetHeight();
	virtual void SetWidth(int newWidth);
	virtual void SetHeight(int newHeight);
	virtual void SetParentElement(UIElement* newParent);
	virtual UIElement* GetParentElement();
	virtual void SetLinkParent(UIElement* newLinkParent);
	virtual UIElement* GetLinkParent();
	virtual void SetLinkedElement(UIElement* newLinkedElement);
	virtual UIElement* GetLinkedElement();
	virtual void SetHirarchy(int newHirarchy);
	virtual int GetHirarchy();
};


class VerticalList : public UIElement
{
	protected:
	vector<UIElement*> ChildElements;
	
	public:
	VerticalList(MenuHandler* newHandler);
	virtual void Attach(UIElement* newElement);
	virtual void Clear();
	virtual int GetWidestChildWidth();
	virtual bool HasChildren();
	virtual bool CheckChildrenForFocus();
	virtual void SetFocus(bool newFocus);
	virtual int HeightOfAllChildren();
	virtual void SetHeightOfChildren(int newHeight);
	virtual void SetPosToMousePos();
	virtual void SetPos(vec2 newPos);
	virtual void RefreshChildPos();
	virtual void SetActive(bool newActive);
};


class Button : public UIElement
{
	protected:
	SDL_Color TextColor;
	string Caption;
	UIElement* linkedElement;
	
	public:
	Button(MenuHandler* newHandler);
	virtual void Update();
	virtual void SetTextColor(int R, int G, int B, int A);
	virtual void SetCaption(string newCaption);
	virtual void Attach(UIElement* newElement);
	virtual void Show();
	virtual bool Clicked();
};


class Label : public UIElement
{
	protected:
	SDL_Color TextColor;
	string Caption;
	
	public:
	Label(MenuHandler* newHandler);
	virtual void SetTextColor(int R, int G, int B, int A);
	virtual void SetCaption(string newCaption);
	virtual void Show();
};






class MenuHandler
{
protected:
	LazyEngine* Engine;
	vector<UIElement*> Elements;
public:
	MenuHandler(LazyEngine* newEngine);
	void Update();
	void AddElement(UIElement* newElement);
	LazyEngine* GetEngine();
	void SetHirarchyForAll(int newHirarchy);
};
