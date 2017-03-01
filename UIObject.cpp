#include "UIObject.h"
#include <iostream>

UIObject::UIObject(LazyEngine* newEngine)
{
	Engine = newEngine;
	pos.x = 10;
	pos.y = 10;
	width = 150;
	height = 50;
	hirarchy = 0;
	timeLastClicked = 0;
	visible = true;
	spanHorizontal = false;
	spanVertical = false;
	Engine->Menu->AddObject(this);
	hirarchy = Engine->Menu->GetHighestHirarchy() + 1;
}
int UIObject::GetHirarchy()
{
	return hirarchy;
}
void UIObject::SetHirarchy(int newHirarchy)
{
	hirarchy = newHirarchy;
}
vec2 UIObject::GetPos()
{
	return pos;
}
void UIObject::SetPos(vec2 newPos)
{
	pos = newPos;
}
int UIObject::GetWidth()
{
	return width;
}
void UIObject::SetWidth(int newWidth)
{
	width = newWidth;
}
int UIObject::GetHeight()
{
	return height;
}
void UIObject::SetHeight(int newHeight)
{
	height = newHeight;
}
bool UIObject::GetVisible()
{
	return visible;
}
void UIObject::SetVisible(bool newVisible)
{
	visible = newVisible;
}
bool UIObject::GetSpanHorizontal()
{
	return spanHorizontal;
}
void UIObject::SetSpanHorizontal(bool newSpanHorizontal)
{
	spanHorizontal = newSpanHorizontal;
}
bool UIObject::GetSpanVertical()
{
	return spanVertical;
}
void UIObject::SetSpanVertical(bool newSpanVertical)
{
	spanVertical = newSpanVertical;
}
vec2 UIObject::GetUsableAreaPos(UIObject* Caller)
{
	return pos;
}
int UIObject::GetUsableAreaWidth(UIObject* Caller)
{
	return width;
}
int UIObject::GetUsableAreaHeight(UIObject* Caller)
{
	return height;
}

void UIObject::Update()
{
	if(Clicked())
	{
		if(hirarchy < Engine->Menu->GetHighestHirarchy())
		{
			hirarchy = Engine->Menu->GetHighestHirarchy() +1;
		}
	}
	Show();
}
void UIObject::Show()
{
	if(MouseOver())
	{
		if(Clicked())
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 150,50,50);
		}
		else
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 100,100,100);
		}
	}
	else
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 50,50,50);
	}
}
bool UIObject::MouseOver()
{
	if(this == Engine->Menu->GetTopObjectAtPos(Engine->Input->GetMousePos()))
	{
		return true;
	}
	return false;
}
bool UIObject::Clicked()
{
	if(MouseOver() && Engine->Input->LeftMouse())
	{	
		if(SDL_GetTicks() - timeLastClicked > 200)
		{
			timeLastClicked = SDL_GetTicks();
			return true;
		}
	}
	return false;
}










UIObject* UIElement::GetParent()
{
	return parent;
}
void UIElement::SetParent(UIObject* newParent)
{
	parent = newParent;
}

UIElement::UIElement(LazyEngine* newEngine) : UIObject(newEngine)
{
	parent = NULL;
}
void UIElement::Show()
{
	if(MouseOver())
	{
		if(Clicked())
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 150,50,50);
		}
		else
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 100,150,100);
		}
	}
	else
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 50,100,50);
	}
}
void UIElement::Update()
{
	if(Clicked())
	{
		if(hirarchy < Engine->Menu->GetHighestHirarchy())
		{
			hirarchy = Engine->Menu->GetHighestHirarchy() +1;
			if(parent != NULL)
			{
				parent->SetHirarchy(hirarchy - 1);
			}
		}
	}
	
	if(parent != NULL)
	{
		pos = parent->GetUsableAreaPos(this);
		if(spanHorizontal)
		{
			width = parent->GetUsableAreaWidth(this);
		}
		if(spanVertical)
		{
			height = parent->GetUsableAreaHeight(this);
		}
	}
	else
	{
		if(spanHorizontal)
		{
			width = Engine->Graphics->GetHorizontalResolution();
		}
		if(spanVertical)
		{
			height = Engine->Graphics->GetVerticalResolution();
		}
	}
	Show();
}











UIContainer::UIContainer(LazyEngine* newEngine) : UIObject(newEngine)
{
	child = NULL;
}
vec2 UIContainer::GetUsableAreaPos(UIObject* Caller)
{
	return vec2(pos.x + 5, pos.y + 5);
}
int UIContainer::GetUsableAreaWidth(UIObject* Caller)
{
	return width - 10;
}
int UIContainer::GetUsableAreaHeight(UIObject* Caller)
{
	return height - 10;
}
void UIContainer::SetChild(UIElement* newChild)
{
	child = newChild;
	child->SetParent(this);
	child->SetSpanHorizontal(true);
	child->SetSpanVertical(true);
}
void UIContainer::Show()
{
	if(MouseOver())
	{
		if(Clicked())
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 150,50,50);
		}
		else
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 100,100,150);
		}
	}
	else
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 50,50,100);
	}
}
void UIContainer::Update()
{
	if(Clicked())
	{
		if(hirarchy < Engine->Menu->GetHighestHirarchy())
		{
			hirarchy = Engine->Menu->GetHighestHirarchy() + 1;
		}
	}
	
	Show();
}
