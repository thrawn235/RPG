#include "UIObject.h"

UIObject::UIObject(LazyEngine* newEngine)
{
	Engine = newEngine;
	pos.x = 10;
	pos.y = 10;
	width = 150;
	height = 50;
	hirarchy = 0;
	Engine->Menu->AddObject(this);
	hirarchy = Engine->Menu->GetHighestHirarchy() + 1; 
}
void UIObject::Update()
{
	Show();
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
		return true;
	}
	return false;
}
