#include "Cursor.h"


MouseCursor::MouseCursor(LazyEngine* newEngine)
{
	Engine = newEngine;
}
void MouseCursor::Update()
{
	Pos = Engine->Input->GetMousePos() + Engine->Graphics->GetCameraPosition();
	//cout<<"Mouse X/Y: "<<Pos.x<<"/"<<Pos.y<<endl;
	Show();
}
void MouseCursor::Show()
{
	//Engine->Graphics->DrawLine(0,0, Pos.x, Pos.y, 200,40,70);
	Engine->Graphics->DrawCircle(Pos.x, Pos.y, 5, 200, 40, 70);
	Engine->Graphics->DrawPoint(Pos.x, Pos.y, 0,0,200);
}
vec2 MouseCursor::GetPos()
{
	return Pos;
}


Cursor::Cursor(LazyEngine* newEngine)
{
	Engine = newEngine;
	clicked = false;
	MousePointer = NULL;
}
void Cursor::Update()
{
	if(MousePointer != NULL)
	{
		Pos = MousePointer->GetPos();
	}
	
	GridPos.x = (int)Pos.x /32;
	GridPos.y = (int)Pos.y /32;
	
	if(Pos.x <= Engine->Graphics->GetCameraPosition().x)
	{
		Engine->Graphics->MoveCamera(-10, 0);
	}
	if(Pos.x >= Engine->Graphics->GetCameraPosition().x + Engine->Graphics->GetHorizontalResolution()-32)
	{
		Engine->Graphics->MoveCamera(10, 0);
	}
	if(Pos.y <= Engine->Graphics->GetCameraPosition().y)
	{
		Engine->Graphics->MoveCamera(0, -10);
	}
	if(Pos.y >= Engine->Graphics->GetCameraPosition().y + Engine->Graphics->GetVerticalResolution()-32)
	{
		Engine->Graphics->MoveCamera(0, 10);
	}
	
	if(Engine->Input->KeyDown(SDLK_UP))
	{
		Pos.y = Pos.y - 32;
	}
	if(Engine->Input->KeyDown(SDLK_DOWN))
	{
		Pos.y = Pos.y + 32;
	}
	if(Engine->Input->KeyDown(SDLK_LEFT))
	{
		Pos.x = Pos.x - 32;
	}
	if(Engine->Input->KeyDown(SDLK_RIGHT))
	{
		Pos.x = Pos.x + 32;
	}
	Show();
}
void Cursor::Show()
{
	Engine->Graphics->DrawRectangle(GridPos.x*32,GridPos.y*32, 32, 32, 200,0,0);
}
vec2 Cursor::GetPos()
{
	return Pos;
}
vec2 Cursor::GetGridPos()
{
	return GridPos;
}
void Cursor::AssignMouse(MouseCursor* newPointer)
{
	MousePointer = newPointer;
}
