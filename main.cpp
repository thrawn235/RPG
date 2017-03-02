#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <glm/vec2.hpp>
#include <iostream>

using namespace std;
using namespace glm;

#include "LazyEngine.h"
#include "Map.h"
#include "Cursor.h"
#include "MapEditor.h"
#include "GameObject.h"


//=======================================================================================
//==================================Main Program=========================================
//=======================================================================================


int main( int argc, char* args[] )
{
	LazyEngine* Engine = new LazyEngine;
	
	Engine->Graphics->Init(800,600,false, "whatever");
	
	Engine->Graphics->LoadSprite("Heroes_01.png", "Heroes", 24,33);
	Engine->Graphics->LoadFont("DejaVuSans.ttf", 8);
	
	GameObject* Test = new GameObject(Engine);
	
	
	MapEditor* Editor = new MapEditor(Engine);
	Cursor* Pointer = new Cursor(Engine);
	Map* currentMap = new Map(Engine);
	MouseCursor* MousePointer = new MouseCursor(Engine);
	
	Pointer->AssignMouse(MousePointer);
	
	Editor->AssignMap(currentMap);
	Editor->InitMap(10,10);
	Editor->LoadTileSet("ground_tiles.png", "Ground", 32,32);
	Editor->SelectTileSet(0);
	Editor->SetCursor(Pointer);
	
	Camera* Cam = Engine->Graphics->GetCamera();
	Cam->SetPos(vec2{-10,-10});
	
	//menu---------------
	UIObject* Button2 = new UIObject(Engine);
	UIContainer* Container = new UIContainer(Engine);
	UIElement* Element = new UIElement(Engine);
	UILabel* Label = new UILabel(Engine);
	UIButton* Button = new UIButton(Engine);
	Element->SetPos(vec2(150, 150));
	Button2->SetPos(vec2(100, 30));
	Container->SetChild(Button);
	Container->SetPos(vec2(200,200));
	Container->SetHeight(120);
	//-------------------
	
	
	//main loop
	long RenderStartTime = 0;
	while(!Engine->End())
	{
		RenderStartTime = SDL_GetTicks();
		Engine->PollEvents();
		
		if(Engine->Input->KeyDown(SDLK_ESCAPE))
		{
			Engine->SetQuit(true);
		}
		
		Engine->Graphics->BeginRender();
					
		currentMap->Update();
		Pointer->Update();
		
		Test->Update();		
		
		Editor->Update();
		MousePointer->Update();
		
		Engine->Menu->Update();
		
		Engine->Graphics->EndRender();
		
		SDL_Delay(30-(SDL_GetTicks()-RenderStartTime));
	}
	
	Engine->Graphics->Destory();
    
    return 0;    
}


//=======================================================================================
//=======================================================================================
//=======================================================================================
