#pragma once

#include <SDL2/SDL.h>
#include <vector>
using namespace std;



class GameObject;
class MenuEngine;
class GraphicsEngine;
class InputEngine;

//------------------------Lazy Engine.h-----------------


class LazyEngine
{


protected:
	vector<GameObject*> GameObjects;
	bool quit;
public:
	GraphicsEngine* Graphics;
	//SoundEngine* Sound;
	InputEngine* Input;
	LazyEngine();
	MenuEngine* Menu;
	void PollEvents();
	void SetQuit(bool newQuit);
	bool End();
};

#include "Graphics.h"
#include "Input.h"
#include "Menu.h"
//-----------------------------------------------------
