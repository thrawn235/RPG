#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <vector>
#include <string>
#include <glm/vec2.hpp>

using namespace std;
using namespace glm;


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
