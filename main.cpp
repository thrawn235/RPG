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

#include "Input.h"
#include "Graphics.h"
#include "LazyEngine.h"
#include "Map.h"
#include "Cursor.h"
#include "MapEditor.h"
#include "GameObject.h"
#include "Menu.h"


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
	
	
	MenuHandler* testmenu = new MenuHandler(Engine);
	
	Label* label1 = new Label(testmenu);
	Label* label2 = new Label(testmenu);
	Label* label3 = new Label(testmenu);
	Label* label4 = new Label(testmenu);
	Label* label5 = new Label(testmenu);
	Label* label6 = new Label(testmenu);
	
	Button* Button1 = new Button(testmenu);
	Button* Button2 = new Button(testmenu);
	Button* Button3 = new Button(testmenu);
	Button* Button4 = new Button(testmenu);
	
	VerticalList* List1 = new VerticalList(testmenu);
	VerticalList* List2 = new VerticalList(testmenu);
	
	List1->Attach(label1);
	List1->Attach(label2);
	List1->Attach(label3);
	List1->Attach(Button1);
	List1->Attach(Button2);
	List1->SetActive(true);
	
	List2->Attach(label4);
	List2->Attach(label5);
	List2->Attach(label6);
	List2->Attach(Button3);
	List2->Attach(Button4);
	
	Button1->Attach(List2);
	
	
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
		
		//Engine->Graphics->DrawText("noch ein test", 0,0);
		
		Test->Update();		
		
		Editor->Update();
		MousePointer->Update();
		
		testmenu->Update();
		
		
		Engine->Graphics->EndRender();
		
		SDL_Delay(30-(SDL_GetTicks()-RenderStartTime));
	}
	
	Engine->Graphics->Destory();
    
    return 0;    
}


//=======================================================================================
//=======================================================================================
//=======================================================================================
