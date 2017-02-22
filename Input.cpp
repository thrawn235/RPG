#include "Input.h"

//------------------Input.cpp------------------------
InputEngine::InputEngine()
{
	LeftMouseButton = false;
	RightMouseButton = false;
}
void InputEngine::getInputEvent(SDL_Event* Event)
{
	if(Event->type == SDL_KEYDOWN)
	{
		//Die ganze sicherheit, fuer den Fall das das event schon in der liste ist. Dann nicht nochmal adden!
		bool found = false;
		for(unsigned int i = 0; i < Keys.size(); i++)
		{
			if(Event->key.keysym.sym == Keys[i])
			{
				found = true;
			}
		}
		if(!found)
		{
			Keys.push_back(Event->key.keysym.sym);
		}
	}
	if(Event->type == SDL_KEYUP)
	{
		for(unsigned int i = 0; i < Keys.size(); i++)
		{
			if(Event->key.keysym.sym == Keys[i])
			{
				Keys.erase(Keys.begin()+i);
			}
		}
	}
	
	if(Event->type == SDL_MOUSEMOTION)
	{
		int x,y;
		SDL_GetMouseState(&x, &y);
		MousePos.x = x;
		MousePos.y = y;
	}
	if(Event->type == SDL_MOUSEBUTTONDOWN)
	{
		if(SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			LeftMouseButton = true;
		}
		if(SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			RightMouseButton = true;
		}
	}
	if(Event->type == SDL_MOUSEBUTTONUP)
	{
		if(SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			LeftMouseButton = false;
		}
		if(SDL_BUTTON(SDL_BUTTON_RIGHT))
		{
			RightMouseButton = false;
		}
	}
}
bool InputEngine::KeyDown(int KeyID)
{
	for(unsigned int i = 0; i < Keys.size(); i++)
	{
		if(KeyID == Keys[i])
		{
			return true;
		}
	}
	return false;
}
bool InputEngine::LeftMouse()
{
	return LeftMouseButton;
}
bool InputEngine::RightMouse()
{
	return RightMouseButton;
}
vec2 InputEngine::GetMousePos()
{
	return MousePos;
}
//-----------------------------------------------------
