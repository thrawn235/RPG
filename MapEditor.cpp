#include "MapEditor.h"


MapEditor::MapEditor(LazyEngine* newEngine)
{
	Engine = newEngine;
	CurrentMap = NULL;
	mode = 1; //0 = off; 1 = MapMode; 2 = TileSetMode;
	CurrentLayer = 1;
	selectedTileSet = NULL;

}
void MapEditor::InitMap(int newWidth, int newHeight)
{
	CurrentMap->InitEmpty(newWidth, newHeight);
}
void MapEditor::AssignMap(Map* newMap)
{
	CurrentMap = newMap;
	CurrentMap->SetShowBorder(true);
	CurrentMap->SetShowGrid(true);
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
