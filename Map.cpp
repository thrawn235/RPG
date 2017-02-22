#include "Map.h"

Map::Map(LazyEngine* newEngine)
{
	width = 0;
	height = 0;
	Engine = newEngine;
	visible = false;
	showBoder = false;
	showGrid = false;
}
void Map::Update()
{
	if(visible)
	{
		Show();
		if(showGrid)
		{
			ShowGrid();
		}
		if(showBoder)
		{
			ShowEdge();
		}
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
void Map::SetShowBorder(bool newShowBorder)
{
	showBoder = newShowBorder;
}
void Map::SetShowGrid(bool newShowGrid)
{
	showGrid = newShowGrid;
}
