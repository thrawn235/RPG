#pragma once

#include <vector>
#include <glm/vec2.hpp>
using namespace std;
using namespace glm;

#include "LazyEngine.h"

class UIObject;

class MenuEngine
{
	private:
	LazyEngine* Engine;
	vector<UIObject*> Objects;
	
	public:
	MenuEngine(LazyEngine* newEngine);
	void AddObject(UIObject* newObject);
	void RemoveObject(UIObject* removeObject);
	void Update();
	vector<UIObject*> GetAllObjects();
	UIObject* GetTopObjectAtPos(vec2 pos);
	vector<UIObject*> GetAllObjectsAtPos(vec2 pos);
	int GetHighestHirarchy();
};

#include "UIObject.h"
