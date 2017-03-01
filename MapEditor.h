#pragma once

#include <SDL2/SDL.h>

#include "LazyEngine.h"
#include "Cursor.h"
#include "Map.h"
#include <iostream>

class LazyEngine;



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
