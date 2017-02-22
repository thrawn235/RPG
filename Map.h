#pragma once

#include <string>
#include <vector>
#include "LazyEngine.h"


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
	bool showGrid;
	bool showBoder;
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
	void SetShowBorder(bool newShowBorder);
	void SetShowGrid(bool newShowBorder);
};
