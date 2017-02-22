#pragma once

#include "Input.h"
#include "Graphics.h"

//------------------------Lazy Engine.h-----------------
class GameObject;

class LazyEngine
{
protected:
	vector<GameObject*> GameObjects;
	bool quit;
public:
	GraphicsEngine* Graphics;
	//SoundEngine* Sound;
	//TimeEngine* Time;
	InputEngine* Input;
	//FileEngine* File;
	//TextEngine* Text;
	//NetworkEngine* Network;
	LazyEngine();
	void PollEvents();
	void SetQuit(bool newQuit);
	bool End();
};
//-----------------------------------------------------
