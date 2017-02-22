#pragma once

#include <SDL2/SDL.h>
#include <glm/vec2.hpp>
#include <vector>
using namespace std;
using namespace glm;

//Input.h--------------------------------------------

class InputEngine
{
protected:
	vector<int> Keys;
	vec2 MousePos;
	bool LeftMouseButton;
	bool RightMouseButton;
public:
	InputEngine();
	void getInputEvent(SDL_Event* Event);
	bool KeyDown(int KeyID);
	bool LeftMouse();
	bool RightMouse();
	vec2 GetMousePos();
};
//---------------------------------------------------
