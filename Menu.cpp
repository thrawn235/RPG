#include "Menu.h"

MenuEngine::MenuEngine(LazyEngine* newEngine)
{
	Engine = newEngine;
}
void MenuEngine::AddObject(UIObject* newObject)
{
	Objects.push_back(newObject);
}
void MenuEngine::RemoveObject(UIObject* removeObject)
{
	for(unsigned int i = 0; i < Objects.size(); i++)
	{
		if(Objects[i] == removeObject)
		{
			Objects.erase(Objects.begin()+i);
		}
	}
}
void MenuEngine::Update()
{
	for(int hirarchy = 0; hirarchy <= GetHighestHirarchy(); hirarchy++)
	{
		for(unsigned int i = 0; i < Objects.size(); i++)
		{
			if(hirarchy == Objects[i]->GetHirarchy())
			{
				Objects[i]->Update();
			}
		}
	}
}
vector<UIObject*> MenuEngine::GetAllObjects()
{
	return Objects;
}
UIObject* MenuEngine::GetTopObjectAtPos(vec2 pos)
{
	UIObject* topObject = NULL;
	
	for(unsigned int i = 0; i < Objects.size(); i++)
	{
		if(pos.x >= Objects[i]->GetPos().x && pos.y >= Objects[i]->GetPos().y)
		{
			if(pos.x <= Objects[i]->GetPos().x + Objects[i]->GetWidth() && pos.y <= Objects[i]->GetPos().y + Objects[i]->GetHeight())
			{
				if(topObject == NULL)
				{
					topObject = Objects[i];
				}
				else
				{
					if(Objects[i]->GetHirarchy() >= topObject->GetHirarchy())
					{
						topObject = Objects[i];
					}
				}
			}
		}
	}
	
	return topObject;
}
vector<UIObject*> MenuEngine::GetAllObjectsAtPos(vec2 pos)
{
	vector<UIObject*> hits;
	
	for(unsigned int i = 0; i < Objects.size(); i++)
	{
		if(pos.x >= Objects[i]->GetPos().x && pos.y >= Objects[i]->GetPos().y)
		{
			if(pos.x <= Objects[i]->GetPos().x + Objects[i]->GetWidth() && pos.y <= Objects[i]->GetPos().y + Objects[i]->GetHeight())
			{
				hits.push_back(Objects[i]);
			}
		}
	}
	return hits;
}
int MenuEngine::GetHighestHirarchy()
{
	int highestHirarchy = 0;
	
	for(unsigned int i = 0; i < Objects.size(); i++)
	{
		if(Objects[i]->GetHirarchy() > highestHirarchy)
		{
			highestHirarchy = Objects[i]->GetHirarchy();
		}
	}
	return highestHirarchy;
}
