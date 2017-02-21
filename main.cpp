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




//=======================================================================================
//=====================================Input Engine======================================
//=======================================================================================


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


//=======================================================================================
//=======================================================================================
//=======================================================================================










//=======================================================================================
//================================Graphics Engine========================================
//=======================================================================================


//Graphics.h------------------------------------------

class Camera
{
	protected:
	vec2 Pos;
	vec2 CenterPos;
	int ResX;
	int ResY;
	
	public:
	Camera();
	vec2 GetPos();
	void SetPos(vec2 newPos);
	void Move(int right, int down);
	void SetResolution(int newResX, int newResY);
	vec2 GetCenterPos();
	void SetCenterPos(vec2 newCenterPos);
};

Camera::Camera()
{
	ResX = 0;
	ResY = 0;
}
vec2 Camera::GetPos()
{
	return Pos;
}
void Camera::SetPos(vec2 newPos)
{
	Pos = newPos;
	CenterPos.x = Pos.x + ResX / 2;
	CenterPos.y = Pos.y + ResY / 2;
}
void Camera::Move(int right, int down)
{
	Pos.x = Pos.x + right;
	Pos.y = Pos.y + down;
	CenterPos.x = CenterPos.x + right;
	CenterPos.y = CenterPos.y + down;
}
void Camera::SetResolution(int newResX, int newResY)
{
	ResX = newResX;
	ResY = newResY;
	CenterPos.x = Pos.x + ResX / 2;
	CenterPos.y = Pos.y + ResY / 2;
}
vec2 Camera::GetCenterPos()
{
	return CenterPos;
}
void Camera::SetCenterPos(vec2 newCenterPos)
{
	CenterPos = newCenterPos;
	Pos = Pos - CenterPos;
}


struct Sprite
{
	int ID;
	SDL_Texture* Texture;
	string Name;
	int SpriteWidth, SpriteHeight;
	int TextureWidth, TextureHeight;
};

class GraphicsEngine
{
protected:
	Camera* Cam;
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	//vector<string> indexedSprites;
	vector<Sprite*> sprites;		//loaded Sprites
	int maxSpriteID;
	int resolutionX;
	int resolutionY;
	int clearR;
	int clearG;
	int clearB;
	TTF_Font* Font;
public:
	GraphicsEngine();
	void Init(int width, int height, bool fullscreen, string title);
	void IndexSprites();
	void LoadSprite(string Path, string Name);
	void LoadSprite(string Path, string Name, int SpriteWidth, int SpriteHeight);
	void LoadSpritefromPalet();
	void LoadAnimationfromPalet();
	void BeginRender();				//ClearScreen
	void EndRender();				//Flip
	void DrawSprite(string TextureName, int posX, int PosY);
	void DrawSprite(string TextureName, int posX, int PosY, int SpriteIndex);
	void DrawPoint(int x, int y, int r, int g, int b);
	void DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b);
	void DrawRectangle(int x1, int y1, int width, int height, int r, int g, int b);
	void DrawFilledRectangle(int x1, int y1, int width, int height, int r, int g, int b);
	void DrawCircle(int x, int y, int radius, int r, int g, int b);
	void DrawText(string Text, int x, int y);
	void DrawSpriteGUI(string TextureName, int posX, int PosY);
	void DrawSpriteGUI(string TextureName, int posX, int PosY, int SpriteIndex);
	void DrawPointGUI(int x, int y, int r, int g, int b);
	void DrawLineGUI(int x1, int y1, int x2, int y2, int r, int g, int b);
	void DrawRectangleGUI(int x1, int y1, int width, int height, int r, int g, int b);
	void DrawFilledRectangleGUI(int x1, int y1, int width, int height, int r, int g, int b);
	void DrawCircleGUI(int x, int y, int radius, int r, int g, int b);
	void DrawTextGUI(string Text, int x, int y);
	void Destory();
	int GetSpriteTextureWidth(string Name);
	int GetSpriteTextureHeight(string Name);
	void MoveCamera(int right, int down);
	vec2 GetCameraPosition();
	int GetVerticalResolution();
	int GetHorizontalResolution();
	Camera* GetCamera();
	void LoadFont(string Filepath, int size);
	
};
//-----------------------------------------------------

//Graphics.cpp-----------------------------------------
GraphicsEngine::GraphicsEngine()
{
	maxSpriteID = 0;
}
void GraphicsEngine::Init(int width, int height, bool fullscreen, string title)
{
	resolutionX = width;
	resolutionY = height;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if(fullscreen)
	{
		SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);
	}
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(Renderer, clearR, clearG, clearB, 0 );
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	
	Cam = new Camera;
}

void GraphicsEngine::LoadSprite(string Path, string Name)
{
	SDL_Surface* Image = IMG_Load(Path.c_str());
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Image);
	SDL_FreeSurface (Image);
	
	Sprite* newSprite = new Sprite;
	newSprite->Name = Name;
	newSprite->Texture = Texture;
	newSprite->ID = maxSpriteID;
	maxSpriteID++;
	
	int width, height;
	SDL_QueryTexture(Texture, NULL, NULL, &width, &height);
	newSprite->TextureWidth = width;
	newSprite->TextureHeight = height;
	newSprite->SpriteHeight = height;
	newSprite->SpriteWidth = width;
	
	sprites.push_back(newSprite);
}

void GraphicsEngine::LoadSprite(string Path, string Name, int SpriteWidth, int SpriteHeight)
{
	SDL_Surface* Image = IMG_Load(Path.c_str());
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Image);
	SDL_FreeSurface (Image);
	
	Sprite* newSprite = new Sprite;
	newSprite->Name = Name;
	newSprite->Texture = Texture;
	
	int width, height;
	SDL_QueryTexture(Texture, NULL, NULL, &width, &height);
	newSprite->TextureWidth = width;
	newSprite->TextureHeight = height;
	newSprite->SpriteHeight = SpriteHeight;
	newSprite->SpriteWidth = SpriteWidth;
	
	sprites.push_back(newSprite);
}

void GraphicsEngine::BeginRender()
{
	//Begin Render
	SDL_SetRenderDrawColor(Renderer, clearR, clearG, clearB, 0 );
	SDL_RenderClear(Renderer);
}

void GraphicsEngine::EndRender()
{
	//End Render
	SDL_RenderPresent(Renderer);
}

void GraphicsEngine::Destory()
{
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

void GraphicsEngine::DrawSprite(string TextureName, int posX, int posY)
{
	int i = 0;
	while(sprites[i]->Name != TextureName)
	{
		i++;
	}
	if(posX > Cam->GetPos().x - sprites[i]->TextureWidth && posX < Cam->GetPos().x + resolutionX && posY > Cam->GetPos().y - sprites[i]->TextureHeight && posY < Cam->GetPos().y + resolutionY)
	{
		SDL_Rect TargetRect{posX-Cam->GetPos().x, posY-Cam->GetPos().y, sprites[i]->TextureWidth, sprites[i]->TextureHeight};
		SDL_RenderCopy (Renderer, sprites[i]->Texture, NULL, &TargetRect);
	}
}

void GraphicsEngine::DrawSprite(string TextureName, int posX, int posY, int SpriteIndex)
{
	int i = 0;
	while(sprites[i]->Name != TextureName)
	{
		i++;
	}
		if(posX > Cam->GetPos().x - sprites[i]->TextureWidth && posX < Cam->GetPos().x + resolutionX && posY > Cam->GetPos().y - sprites[i]->TextureHeight && posY < Cam->GetPos().y + resolutionY)
		{
		int SourcePosX = 0;
		int SourcePosY = 0;
		int si = 0;
		while(si < SpriteIndex)
		{
			SourcePosX = SourcePosX + sprites[i]->SpriteWidth;
			if(SourcePosX > sprites[i]->TextureWidth - sprites[i]->SpriteWidth)
			{
				SourcePosX = 0;
				SourcePosY = SourcePosY + sprites[i]->SpriteHeight;
			}
			si++;
		}
		
		SDL_Rect SourceRect{SourcePosX, SourcePosY, sprites[i]->SpriteWidth, sprites[i]->SpriteHeight};
		SDL_Rect TargetRect{posX-Cam->GetPos().x, posY-Cam->GetPos().y, sprites[i]->SpriteWidth, sprites[i]->SpriteHeight};
		SDL_RenderCopy (Renderer, sprites[i]->Texture, &SourceRect, &TargetRect);
	}
}

void GraphicsEngine::DrawPoint(int x, int y, int r, int g, int b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, 0 );
	SDL_RenderDrawPoint(Renderer, x-Cam->GetPos().x, y-Cam->GetPos().y);
}
void GraphicsEngine::DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, 0 );
	SDL_RenderDrawLine(Renderer, x1-Cam->GetPos().x, y1-Cam->GetPos().y, x2-Cam->GetPos().x, y2-Cam->GetPos().y);
}
void GraphicsEngine::DrawRectangle(int x, int y, int width, int height, int r, int g, int b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, 0 );
	SDL_RenderDrawLine(Renderer, x-Cam->GetPos().x, y-Cam->GetPos().y, x+width-Cam->GetPos().x, y-Cam->GetPos().y);
	SDL_RenderDrawLine(Renderer, x-Cam->GetPos().x, y-Cam->GetPos().y, x-Cam->GetPos().x, y+height-Cam->GetPos().y);
	SDL_RenderDrawLine(Renderer, x+width-Cam->GetPos().x, y-Cam->GetPos().y, x+width-Cam->GetPos().x, y+height-Cam->GetPos().y);
	SDL_RenderDrawLine(Renderer, x-Cam->GetPos().x, y+height-Cam->GetPos().y, x+width-Cam->GetPos().x, y+height-Cam->GetPos().y);
}
void GraphicsEngine::DrawFilledRectangle(int x, int y, int width, int height, int r, int g, int b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, 0 );
	SDL_Rect Rect{x-Cam->GetPos().x,y-Cam->GetPos().y,width,height};
	SDL_RenderFillRect(Renderer, &Rect);
}
void GraphicsEngine::DrawCircle(int x, int y, int radius, int r, int g, int b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, 255 );
	circleRGBA(Renderer,x-Cam->GetPos().x, y-Cam->GetPos().y, radius,r, g, b,255);
}
void GraphicsEngine::DrawText(string Text, int x, int y)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, Text.c_str(), SDL_Color{255,255,255}); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Renderer, surfaceMessage); //now you can convert it into a texture
	SDL_FreeSurface(surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x-Cam->GetPos().x;  //controls the rect's x coordinate 
	Message_rect.y = y-Cam->GetPos().y; // controls the rect's y coordinte
	SDL_QueryTexture(Message, NULL, NULL, &Message_rect.w, &Message_rect.h);

	SDL_RenderCopy(Renderer, Message, NULL, &Message_rect);
	
	SDL_DestroyTexture(Message);
}
void GraphicsEngine::DrawSpriteGUI(string TextureName, int posX, int posY)
{
	int i = 0;
	while(sprites[i]->Name != TextureName)
	{
		i++;
	}
	
	SDL_Rect TargetRect{posX, posY, sprites[i]->TextureWidth, sprites[i]->TextureHeight};
	SDL_RenderCopy (Renderer, sprites[i]->Texture, NULL, &TargetRect);
}

void GraphicsEngine::DrawSpriteGUI(string TextureName, int posX, int posY, int SpriteIndex)
{
	int i = 0;
	while(sprites[i]->Name != TextureName)
	{
		i++;
	}
	int SourcePosX = 0;
	int SourcePosY = 0;
	int si = 0;
	while(si < SpriteIndex)
	{
		SourcePosX = SourcePosX + sprites[i]->SpriteWidth;
		if(SourcePosX > sprites[i]->TextureWidth - sprites[i]->SpriteWidth)
		{
			SourcePosX = 0;
			SourcePosY = SourcePosY + sprites[i]->SpriteHeight;
		}
		si++;
	}
	
	SDL_Rect SourceRect{SourcePosX, SourcePosY, sprites[i]->SpriteWidth, sprites[i]->SpriteHeight};
	SDL_Rect TargetRect{posX, posY, sprites[i]->SpriteWidth, sprites[i]->SpriteHeight};
	SDL_RenderCopy (Renderer, sprites[i]->Texture, &SourceRect, &TargetRect);
}

void GraphicsEngine::DrawPointGUI(int x, int y, int r, int g, int b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, 0 );
	SDL_RenderDrawPoint(Renderer, x, y);
}
void GraphicsEngine::DrawLineGUI(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, 0 );
	SDL_RenderDrawLine(Renderer, x1, y1, x2, y2);
}
void GraphicsEngine::DrawRectangleGUI(int x, int y, int width, int height, int r, int g, int b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, 0 );
	SDL_RenderDrawLine(Renderer, x, y, x+width, y);
	SDL_RenderDrawLine(Renderer, x, y, x, y+height);
	SDL_RenderDrawLine(Renderer, x+width, y, x+width, y+height);
	SDL_RenderDrawLine(Renderer, x, y+height, x+width, y+height);
}
void GraphicsEngine::DrawFilledRectangleGUI(int x, int y, int width, int height, int r, int g, int b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, 0 );
	SDL_Rect Rect{x,y,width,height};
	SDL_RenderFillRect(Renderer, &Rect);
}
void GraphicsEngine::DrawCircleGUI(int x, int y, int radius, int r, int g, int b)
{
	SDL_SetRenderDrawColor(Renderer, r, g, b, 255 );
	circleRGBA(Renderer,x, y, radius,r, g, b,255);
}
void GraphicsEngine::DrawTextGUI(string Text, int x, int y)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, Text.c_str(), SDL_Color{255,255,255}); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Renderer, surfaceMessage); //now you can convert it into a texture
	SDL_FreeSurface(surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
	SDL_QueryTexture(Message, NULL, NULL, &Message_rect.w, &Message_rect.h);

	SDL_RenderCopy(Renderer, Message, NULL, &Message_rect);
	
	SDL_DestroyTexture(Message);
}
int GraphicsEngine::GetSpriteTextureWidth(string Name)
{
	for(unsigned int i = 0; i < sprites.size(); i++)
	{
		if(sprites[i]->Name == Name)
		{
			return sprites[i]->TextureWidth;
		}
	}
	return 0;
}
int GraphicsEngine::GetSpriteTextureHeight(string Name)
{
	for(unsigned int i = 0; i < sprites.size(); i++)
	{
		if(sprites[i]->Name == Name)
		{
			return sprites[i]->TextureHeight;
		}
	}
	return 0;
}
Camera* GraphicsEngine::GetCamera()
{
	return Cam;
}
void GraphicsEngine::MoveCamera(int right, int down)
{
	Cam->Move(right, down);
}
vec2 GraphicsEngine::GetCameraPosition()
{
	return Cam->GetPos();
}
int GraphicsEngine::GetVerticalResolution()
{
	return resolutionY;
}
int GraphicsEngine::GetHorizontalResolution()
{
	return resolutionX;
}
void GraphicsEngine::LoadFont(string Filepath, int size)
{
	Font = TTF_OpenFont( Filepath.c_str(), size );
}
//-----------------------------------------------------


//=======================================================================================
//=======================================================================================
//=======================================================================================










//=======================================================================================
//=====================================Lazy Engine=======================================
//=======================================================================================


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

//---------------------Lazy Engine.cpp-----------------
LazyEngine::LazyEngine()
{
	Graphics = new GraphicsEngine;
	Input = new InputEngine;
	quit = false;
}
void LazyEngine::PollEvents()
{
	SDL_Event Event;
	while(SDL_PollEvent(&Event) != 0)
	{
		if(Event.type == SDL_QUIT)
		{
			quit = true;
		}
		else
		{
			Input->getInputEvent(&Event);
		}
	}
}
bool LazyEngine::End()
{
	return quit;
}
void LazyEngine::SetQuit(bool newQuit)
{
	quit = newQuit;
}
//-----------------------------------------------------


//=======================================================================================
//=======================================================================================
//=======================================================================================










//=======================================================================================
//======================================Menu=============================================
//=======================================================================================

/* The Idea is: You create and fill this Datastructure before Hand, for Example in the GameObjects Constructor
 * The Drawing and Checking is done in the mainloop. In the Update or Show Methods for example */
 
/* Menu Is not a GameObject. It is supposed to exist in another GameOjbect*/

//Idea: The Menu could have a pointer to a sub menu!

class Menu
{
protected:
	LazyEngine* Engine;
	vec2 Pos;
	int width;
	int height;
	vector<string> Entries;
	SDL_Color BorderColor;
	SDL_Color BackgroundColor;
	SDL_Color TextColor;
	bool mouseOver;
	int mouseOverEntry;
	//int highlitedEntry;
	bool vertical;  //horizontal menus span the entire Screen
	vector<Menu*> subMenus;
	bool active;
	int EntryPos;
	bool focus;
	bool MainMenu;
	Menu* parentMenu;
	int lastInputTime;
public:
	Menu(LazyEngine* newEngine);
	void DrawSelf();
	void AddEntry(string newEntry);
	void Clear();
	void NewEntries(vector<string> newEntries);
	void SetBorderColor(int R, int G, int B);
	void SetBackgroundColor(int R, int G, int B);
	void SetTextColor(int R, int G, int B);
	void CheckMousePos();
	void ChangeOrientation();
	bool MouseOver();
	int MouseOverEntry();
	void SetPos(vec2 newPos);
	void SetPosToMousePos();
	void Update();
	void AddSubMenu(Menu* newMenu, int newEntryPos);
	bool Clicked(int checkEntry);
	bool IsActive();
	void SetActive(bool newActive);
	void ToggleActive();
	int GetEntryPos();
	void SetFocus(bool newFocus);
	bool GetFocus();
	void SetParentMenu(Menu* newParentMenu);
	Menu* GetParentMenu();
	bool CheckChildrenForFocus();
};

Menu::Menu(LazyEngine* newEngine)
{
	Engine = newEngine;
	width = 150;
	height = 10;
	BorderColor = {255,255,255,255};
	BackgroundColor = {50,50,50,255};
	TextColor = {255,255,255,255};
	mouseOver = false;
	mouseOverEntry = -1;
	vertical = true;  //horizontal menus span the entire Screen
	active = false;
	focus = true;
	EntryPos = 0;
	parentMenu = NULL;
	lastInputTime = 0;
}
void Menu::DrawSelf()
{
	if(vertical)
	{
		if(mouseOver == true)
		{
			Engine->Graphics->DrawFilledRectangleGUI(Pos.x,Pos.y, width, Entries.size()*20, BackgroundColor.r,BackgroundColor.g,BackgroundColor.b);
			if(mouseOverEntry >= 0)
			{
				Engine->Graphics->DrawFilledRectangleGUI(Pos.x,Pos.y+(mouseOverEntry*20), width, 20, BackgroundColor.r*2,BackgroundColor.g*2,BackgroundColor.b*2);
			}
			Engine->Graphics->DrawRectangleGUI(Pos.x,Pos.y, width, Entries.size()*20, BorderColor.r,BorderColor.g,BorderColor.b);
			for(unsigned int i = 0; i < Entries.size(); i++)
			{
				Engine->Graphics->DrawTextGUI(Entries[i], Pos.x+10, Pos.y+(i*20)+5);
			}
		}
		else
		{
			Engine->Graphics->DrawFilledRectangleGUI(Pos.x,Pos.y, width, Entries.size()*20, BackgroundColor.r/2,BackgroundColor.g/2,BackgroundColor.b/2);
			Engine->Graphics->DrawRectangleGUI(Pos.x,Pos.y, width, Entries.size()*20, BorderColor.r/2,BorderColor.g/2,BorderColor.b/2);
			for(unsigned int i = 0; i < Entries.size(); i++)
			{
				Engine->Graphics->DrawTextGUI(Entries[i], Pos.x+10, Pos.y+(i*20)+5);
			}
		}
	}
	else //horizontal
	{
		if(mouseOver == true)
		{
			Engine->Graphics->DrawFilledRectangleGUI(Pos.x,Pos.y, Engine->Graphics->GetHorizontalResolution(), 20, BackgroundColor.r/2,BackgroundColor.g/2,BackgroundColor.b/2);
			if(mouseOverEntry >= 0)
			{
				Engine->Graphics->DrawFilledRectangleGUI(Pos.x+(Engine->Graphics->GetHorizontalResolution()/Entries.size())*mouseOverEntry, Pos.y, Engine->Graphics->GetHorizontalResolution()/Entries.size(), 20, BackgroundColor.r*2,BackgroundColor.g*2,BackgroundColor.b*2);
			}
			Engine->Graphics->DrawRectangleGUI(Pos.x,Pos.y, Engine->Graphics->GetHorizontalResolution(), 20, BorderColor.r/2,BorderColor.g/2,BorderColor.b/2);
			for(unsigned int i = 0; i < Entries.size(); i++)
			{
				Engine->Graphics->DrawTextGUI(Entries[i], Pos.x+((Engine->Graphics->GetHorizontalResolution()/Entries.size())*i)+5, Pos.y+5);
			}
		}
		else
		{
			Engine->Graphics->DrawFilledRectangleGUI(Pos.x,Pos.y, Engine->Graphics->GetHorizontalResolution(), 20, BackgroundColor.r/2,BackgroundColor.g/2,BackgroundColor.b/2);
			Engine->Graphics->DrawRectangleGUI(Pos.x,Pos.y, Engine->Graphics->GetHorizontalResolution(), 20, BorderColor.r/2,BorderColor.g/2,BorderColor.b/2);
			for(unsigned int i = 0; i < Entries.size(); i++)
			{
				Engine->Graphics->DrawTextGUI(Entries[i], Pos.x+((Engine->Graphics->GetHorizontalResolution()/Entries.size())*i)+5, Pos.y+5);
			}
		}
	}
}
void Menu::AddEntry(string newEntry)
{
	Entries.push_back(newEntry);
}
void Menu::Clear()
{
	Entries.clear();
}
void Menu::NewEntries(vector<string> newEntries)
{
	Clear();
	Entries = newEntries;
}
void Menu::SetBorderColor(int R, int G, int B)
{
	BorderColor.r = R;
	BorderColor.g = G;
	BorderColor.b = B;
}
void Menu::SetBackgroundColor(int R, int G, int B)
{
	BackgroundColor.r = R;
	BackgroundColor.g = G;
	BackgroundColor.b = B;
}
void Menu::SetTextColor(int R, int G, int B)
{
	TextColor.r = R;
	TextColor.g = G;
	TextColor.b = B;
}
void Menu::CheckMousePos()
{
	if(vertical)
	{
		if(Engine->Input->GetMousePos().x < Pos.x+width && Engine->Input->GetMousePos().x > Pos.x)
		{
			if(Engine->Input->GetMousePos().y < Pos.y+Entries.size()*20 && Engine->Input->GetMousePos().y > Pos.y)
			{
				mouseOver = true;
			}
		}
		else
		{
			mouseOver = false;
		}
		
		if((Engine->Input->GetMousePos().y - Pos.y) / 20 >= 0 && (Engine->Input->GetMousePos().y - Pos.y) / 20 <= Entries.size())
		{ 
			mouseOverEntry = (int)(Engine->Input->GetMousePos().y - Pos.y) / 20;
		}
		else
		{
			mouseOverEntry = -1;
		}
	}
	else //horizontal
	{
		if(Engine->Input->GetMousePos().y < Pos.y+20 && Engine->Input->GetMousePos().y > Pos.y)
		{
			mouseOver = true;
		}
		else
		{
			mouseOver = false;
		}
		
		mouseOverEntry = (int)Engine->Input->GetMousePos().x / (Engine->Graphics->GetHorizontalResolution() / Entries.size());
	}
}
void Menu::ChangeOrientation()
{
	vertical = !vertical;
}
bool Menu::MouseOver()
{
	return mouseOver;
}
int Menu::MouseOverEntry()
{
	return mouseOverEntry;
}
void Menu::SetPos(vec2 newPos)
{
	Pos = newPos;
}
void Menu::SetPosToMousePos()
{
	Pos = Engine->Input->GetMousePos()-vec2(5,5);
}
void Menu::Update()
{
	CheckMousePos();
	DrawSelf();
	
	if(!mouseOver && Engine->Input->LeftMouse())
	{
		if(CheckChildrenForFocus() == true)
		{
			SetActive(true);
		}
		else
		{
			SetActive(false);
		}
		
		
		SetFocus(false);
		if(parentMenu == NULL)
		{
			if(CheckChildrenForFocus() == false)
			{
				SetFocus(true);
			}
		}
	}
	if(mouseOver && Engine->Input->LeftMouse() && !focus)
	{
		SetActive(true);
		SetFocus(true);
	}
	
	for(unsigned int i = 0; i < Entries.size(); i++)
	{
		if(Clicked(i))
		{
			/*if(!CheckChildrenForFocus())
			{
				focus = false;
				active = false;
			}*/
			for(unsigned int u = 0; u < subMenus.size(); u++)
			{
				if(subMenus[u]->GetEntryPos() == i)
				{
					if(!subMenus[u]->IsActive())
					{
						subMenus[u]->SetPosToMousePos();
						subMenus[u]->SetActive(true);
						focus = false;
						subMenus[u]->SetFocus(true);
					}
				}
			}
		}
	}
	
	for(unsigned int i = 0; i < subMenus.size(); i++)
	{
		if(subMenus[i]->IsActive())
		{
			subMenus[i]->Update();
		}
	}
}
void Menu::AddSubMenu(Menu* newMenu, int newEntryPos)
{
	newMenu->EntryPos = newEntryPos;
	newMenu->SetParentMenu(this);
	newMenu->SetFocus(false);
	subMenus.push_back(newMenu);
}
bool Menu::Clicked(int checkEntry)
{
	
	if(MouseOver() && Engine->Input->LeftMouse() && focus)
	{
		for(unsigned int i = 0; i < Entries.size(); i++)
		{
			if(MouseOverEntry() == checkEntry)
			{
				return true;
			}
		}
	}
	return false;
}
bool Menu::IsActive()
{
	return active;
}
void Menu::SetActive(bool newActive)
{
	active = newActive;
}
void Menu::ToggleActive()
{
	active = !active;
}
int Menu::GetEntryPos()
{
	return EntryPos;
}
void Menu::SetFocus(bool newFocus)
{
	focus = newFocus;
}
bool Menu::GetFocus()
{
	return focus;
}
void Menu::SetParentMenu(Menu* newParentMenu)
{
	parentMenu = newParentMenu;
}
Menu* Menu::GetParentMenu()
{
	return parentMenu;
}
bool Menu::CheckChildrenForFocus()
{
	bool status = false;
	for(unsigned int i = 0; i < subMenus.size(); i++)
	{
		if(subMenus[i]->CheckChildrenForFocus())
		{
			status = true;
		}
	}
	return status;
}

//=======================================================================================
//=======================================================================================
//=======================================================================================










//=======================================================================================
//==================================Game Object==========================================
//=======================================================================================

class GameObject
{
protected:
	LazyEngine* Engine;
	int PosX;
	int PosY;
public:
	GameObject(LazyEngine* newEngine);
	void Move();
	void Show();
	void Update();
};

GameObject::GameObject(LazyEngine* newEngine)
{
	PosX = 0;
	PosY = 0;
	Engine = newEngine;
}

void GameObject::Move()
{
	PosX++;
}

void GameObject::Show()
{
	Engine->Graphics->DrawSprite("Heroes", PosX, PosY, 25);
}

void GameObject::Update()
{
	Move();
	Show();
}

//=======================================================================================
//=======================================================================================
//=======================================================================================










//=======================================================================================
//==================================Map==================================================
//=======================================================================================

struct TileSet
{
	int tileSetID;
	string tileSetName;
	int width;
	int height;
};

struct TileID
{
	int ID;
	int tileSetID;
};

struct TileData
{
	int ID;
	int tileSetID;
	bool collisionMask[4][4];
};

class Map
{
protected:
	LazyEngine* Engine;
	bool visible;
public:
	int width;
	int height;
	vector< vector< TileID > > objectLayer;
	vector< vector< TileID > > groundLayer;
	vector< vector< TileID > > subLayer;
	vector<TileSet*> TileSets;
	
	Map(LazyEngine* newEngine);
	void Update();
	void Show();
	void SetVisible(bool newVisible);
	bool getVisible();
	void InitEmpty(int width, int height);
	void ShowGrid();
	void ShowEdge();
};

Map::Map(LazyEngine* newEngine)
{
	width = 0;
	height = 0;
	Engine = newEngine;
	visible = false;
}
void Map::Update()
{
	if(visible)
	{
		Show();
		ShowGrid();
		ShowEdge();
	}
}
void Map::Show()
{
	for(unsigned int i = 0; i < subLayer.size(); i++)
	{
		for(unsigned int u = 0; u < subLayer[i].size(); u++)
		{
			for(unsigned int o = 0; o < TileSets.size(); o++)
			{	
				if(TileSets[o]->tileSetID == subLayer[i][u].tileSetID)
				{
					Engine->Graphics->DrawSprite(TileSets[o]->tileSetName, i*32, u*32, subLayer[i][u].ID);
					//Engine->Graphics->DrawText(to_string(subLayer[i][u].tileSetID), (i*32)+2, (u*32)+15); //memory overflow ?????
				}
			}	
			//Engine->Graphics->DrawText(to_string(subLayer[i][u].ID), (i*32)+2, (u*32)+3);
			
		}
	}
	
	for(unsigned int i = 0; i < groundLayer.size(); i++)
	{
		for(unsigned int u = 0; u < groundLayer[i].size(); u++)
		{
			for(unsigned int o = 0; o < TileSets.size(); o++)
			{	
				if(TileSets[o]->tileSetID == groundLayer[i][u].tileSetID)
				{
					Engine->Graphics->DrawSprite(TileSets[o]->tileSetName, i*32, u*32, groundLayer[i][u].ID);
					//cout<<"Spam... tileset: "<<TileSets[0]->tileSetName<<" ID: "<<groundLayer[i][u].ID<<endl;
					//Engine->Graphics->DrawText(to_string(groundLayer[i][u].tileSetID), (i*32)+12, (u*32)+15); //memory overflow ?????
				}
			}	
			//Engine->Graphics->DrawText(to_string(groundLayer[i][u].ID), (i*32)+12, (u*32)+3);
			
		}
	}
	
	for(unsigned int i = 0; i < objectLayer.size(); i++)
	{
		for(unsigned int u = 0; u < objectLayer[i].size(); u++)
		{
			for(unsigned int o = 0; o < TileSets.size(); o++)
			{	
				if(TileSets[o]->tileSetID == objectLayer[i][u].tileSetID)
				{
					Engine->Graphics->DrawSprite(TileSets[o]->tileSetName, i*32, u*32, objectLayer[i][u].ID);
					//Engine->Graphics->DrawText(to_string(objectLayer[i][u].tileSetID), (i*32)+22, (u*32)+15); //memory overflow ?????
				}
			}	
			//Engine->Graphics->DrawText(to_string(objectLayer[i][u].ID), (i*32)+22, (u*32)+3);
			
		}
	}
}
void Map::SetVisible(bool newVisible)
{
	visible = newVisible;
}
bool Map::getVisible()
{
	return visible;
}
void Map::InitEmpty(int newWidth, int newHeight)
{
	groundLayer.clear();
	
	width = newWidth;
	height = newHeight;
	
	TileID emptyTile;
	emptyTile.ID = -1;
	emptyTile.tileSetID = -1;
	
	for(int i = 0; i < height; i++)
	{
		vector<TileID> row;
		groundLayer.push_back(row);
		objectLayer.push_back(row);
		subLayer.push_back(row);
		for(int u = 0; u < width; u++)
		{
			objectLayer[i].push_back(emptyTile);
			groundLayer[i].push_back(emptyTile);
			subLayer[i].push_back(emptyTile);
		}
	}
}
void Map::ShowGrid()
{
	for(int i = 0; i < height; i++)
	{
		Engine->Graphics->DrawLine(i*32, 0, i*32, 32*width, 255,255,255);
		for(int u = 0; u < width; u++)
		{
			Engine->Graphics->DrawLine(0, u*32, 32*height, u*32, 255,255,255);
		}
	}
}
void Map::ShowEdge()
{
	Engine->Graphics->DrawRectangle(0,0, height*32, width*32, 0,100,0);
}


//=======================================================================================
//=======================================================================================
//=======================================================================================










//=======================================================================================
//====================================Cursor=============================================
//=======================================================================================

class MouseCursor
{
	protected:
	LazyEngine* Engine;
	vec2 Pos;
	
	public:
	MouseCursor(LazyEngine* newEngine);
	void Update();
	void Show();
	vec2 GetPos();
};

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



class Cursor
{
	protected:
	LazyEngine* Engine;
	MouseCursor* MousePointer;
	vec2 Pos;
	vec2 GridPos;
	bool clicked;
	
	public:
	Cursor(LazyEngine* newEngine);
	void Update();
	void Show();
	vec2 GetPos();
	vec2 GetGridPos();
	void AssignMouse(MouseCursor* newPointer);
};

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

//=======================================================================================
//=======================================================================================
//=======================================================================================










//=======================================================================================
//====================================Map Editor=========================================
//=======================================================================================


class MapEditor
{
protected:
	LazyEngine* Engine;
	Map* CurrentMap;
	Cursor* pCursor;
	int mode;
	int CurrentLayer;
	TileSet* selectedTileSet;
	TileID selectedTile;
	Menu* MainMenu;
	Menu* FileMenu;
	Menu* LayerMenu;
	Menu* ViewMenu;
	Menu* TileSetsMenu;
	Menu* thirdLevelMenu;
	
public:
	MapEditor(LazyEngine* newEngine);
	void AssignMap(Map* newMap);
	void InitMap(int newWidth, int newHeight);
	void ClearMap();
	void SetSize(int newWidth, int newHeight);
	void LoadTileSet(string filename, string tileSetName, int width, int height);
	void DrawTileSet(string tileSetName);
	void Show();
	void SelectTileSet(int newID);
	void Update();
	void SetCursor(Cursor* newCursor);
};

MapEditor::MapEditor(LazyEngine* newEngine)
{
	Engine = newEngine;
	CurrentMap = NULL;
	mode = 1; //0 = off; 1 = MapMode; 2 = TileSetMode;
	CurrentLayer = 1;
	selectedTileSet = NULL;
	MainMenu = new Menu(Engine);
	MainMenu->NewEntries({"File","Layer","View","TileSets","Map"});
	MainMenu->ChangeOrientation();
	FileMenu = new Menu(Engine);
	FileMenu->NewEntries({"Load","Save","Quit"});
	LayerMenu = new Menu(Engine);
	LayerMenu->NewEntries({"Select Sub","Select Ground","Select Object"});
	ViewMenu = new Menu(Engine);
	ViewMenu->NewEntries({"Show Grid","Disable Grid"});
	TileSetsMenu = new Menu(Engine);
	TileSetsMenu->NewEntries({"Load", "Show Current Set"});
	MainMenu->AddSubMenu(FileMenu, 0);
	MainMenu->AddSubMenu(LayerMenu, 1);
	MainMenu->AddSubMenu(ViewMenu, 2);
	MainMenu->AddSubMenu(TileSetsMenu, 3);
	thirdLevelMenu = new Menu(Engine);
	thirdLevelMenu->NewEntries({"nur","ein","test"});
	LayerMenu->AddSubMenu(thirdLevelMenu, 1);
}
void MapEditor::InitMap(int newWidth, int newHeight)
{
	CurrentMap->InitEmpty(newWidth, newHeight);
}
void MapEditor::AssignMap(Map* newMap)
{
	CurrentMap = newMap;
}
void MapEditor::ClearMap()
{
	//nicht fertig
}
//void MapEditor::SetSize(int newWidth, int newHeight);
void MapEditor::LoadTileSet(string filename, string tileSetName, int width, int height)
{
	if(CurrentMap != NULL)
	{
		Engine->Graphics->LoadSprite(filename, tileSetName, width, height);
		
		TileSet* newTileSet = new TileSet;
		newTileSet->tileSetID = CurrentMap->TileSets.size(); //problem: wenn die liste kleiner wird stimmen die IDS nicht mehr
		newTileSet->tileSetName = tileSetName;
		newTileSet->width = Engine->Graphics->GetSpriteTextureWidth(tileSetName);
		newTileSet->height = Engine->Graphics->GetSpriteTextureHeight(tileSetName);
		CurrentMap->TileSets.push_back(newTileSet);
		cout<<"trying to load Tileset ID: "<<newTileSet->tileSetID<<" Name: "<<newTileSet->tileSetName<<" W: "<<newTileSet->width<<" H: "<<newTileSet->height<<endl;
	}
}
void MapEditor::DrawTileSet(string tileSetName)
{
	Engine->Graphics->DrawSprite(tileSetName, 0,0);
}
void MapEditor::Show()
{
	
	
	if(mode == 0)
	{
	}
	if(mode == 1)
	{
		//Map
		CurrentMap->SetVisible(true);
	}
	if(mode == 2)
	{
		//TileSet
		CurrentMap->SetVisible(false);
		if(selectedTileSet != NULL)
		{
			Engine->Graphics->DrawFilledRectangle(0,0, selectedTileSet->width, selectedTileSet->height, 50,0,0);
			Engine->Graphics->DrawSprite(selectedTileSet->tileSetName, 0,0);
		}
	}
}
void MapEditor::SelectTileSet(int newID)
{
	for(unsigned int i = 0; i < CurrentMap->TileSets.size(); i++)
	{
		if(CurrentMap->TileSets[i]->tileSetID == newID)
		{
			selectedTileSet = CurrentMap->TileSets[i];
			cout<<"trying to select Tile set ID: "<<selectedTileSet->tileSetID<<" Name: "<<selectedTileSet->tileSetName<<" W: "<<selectedTileSet->width<<" H: "<<selectedTileSet->height<<endl;
		}
	}
}
void MapEditor::Update()
{
	//Menu-------------------------------
	MainMenu->Update();
	if(FileMenu->Clicked(2))
	{
		Engine->SetQuit(true);
	}
	
	if(TileSetsMenu->Clicked(1))
	{
		if(mode == 1)
		{
			mode = 2;
		}
		else if(mode == 2)
		{
			mode = 1;
		}
	}
	//-----------------------------------
	
	if(mode == 2)
	{
		if(Engine->Input->KeyDown(SDLK_SPACE) || Engine->Input->LeftMouse())
		{
			selectedTile.ID = pCursor->GetGridPos().x+pCursor->GetGridPos().y + (pCursor->GetGridPos().y*20); //falsche zahl!
			selectedTile.tileSetID = selectedTileSet->tileSetID;
		}
	}
	if(mode == 1)
	{
		if(Engine->Input->KeyDown(SDLK_SPACE) || Engine->Input->LeftMouse())
		{
			if(pCursor->GetPos().x > 0 && pCursor->GetPos().x < CurrentMap->width*32 && pCursor->GetPos().y > 0 && pCursor->GetPos().y < CurrentMap->height*32)
			{
				//Engine->Graphics->DrawText(to_string(CurrentMap->groundLayer[pCursor->GetGridPos().x][pCursor->GetGridPos().y].ID), (pCursor->GetGridPos().x*32)+10, (pCursor->GetGridPos().y*32)+3);
				if(CurrentLayer == 1)
				{
					CurrentMap->subLayer[pCursor->GetGridPos().x][pCursor->GetGridPos().y] = selectedTile;
				}
				if(CurrentLayer == 2)
				{
					CurrentMap->groundLayer[pCursor->GetGridPos().x][pCursor->GetGridPos().y] = selectedTile;
				}
				if(CurrentLayer == 3)
				{
					CurrentMap->objectLayer[pCursor->GetGridPos().x][pCursor->GetGridPos().y] = selectedTile;
				}
			}
		}
	}
	
	if(Engine->Input->KeyDown(SDLK_F1))
	{
		mode = 1;
	}
	if(Engine->Input->KeyDown(SDLK_F2))
	{
		mode = 2;
	}
	if(Engine->Input->KeyDown(SDLK_1))
	{
		CurrentLayer = 1;
	}
	if(Engine->Input->KeyDown(SDLK_2))
	{
		CurrentLayer = 2;
	}
	if(Engine->Input->KeyDown(SDLK_3))
	{
		CurrentLayer = 3;
	}
	
	Show();
}
void MapEditor::SetCursor(Cursor* newCursor)
{
	pCursor = newCursor;
}

//=======================================================================================
//=======================================================================================
//=======================================================================================







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
		
		Engine->Graphics->EndRender();
		
		SDL_Delay(30-(SDL_GetTicks()-RenderStartTime));
	}
	
	Engine->Graphics->Destory();
    
    return 0;    
}


//=======================================================================================
//=======================================================================================
//=======================================================================================
