#include "UIObject.h"

UIObject::UIObject(LazyEngine* newEngine)
{
	Engine = newEngine;
	pos.x = 10;
	pos.y = 10;
	width = 150;
	height = 50;
	hirarchy = 0;
	timeLastClicked = 0;
	visible = true;
	spanHorizontal = false;
	spanVertical = false;
	lockHirarchy = false;
	Engine->Menu->AddObject(this);
	hirarchy = Engine->Menu->GetHighestHirarchy() + 1;
}
int UIObject::GetHirarchy()
{
	return hirarchy;
}
void UIObject::SetHirarchy(int newHirarchy)
{
	if(!lockHirarchy)
	{
		lockHirarchy = true;
		hirarchy = newHirarchy;
	}
}
vec2 UIObject::GetPos()
{
	return pos;
}
void UIObject::SetPos(vec2 newPos)
{
	pos = newPos;
}
int UIObject::GetWidth()
{
	return width;
}
void UIObject::SetWidth(int newWidth)
{
	width = newWidth;
}
int UIObject::GetHeight()
{
	return height;
}
void UIObject::SetHeight(int newHeight)
{
	height = newHeight;
}
bool UIObject::GetVisible()
{
	return visible;
}
void UIObject::SetVisible(bool newVisible)
{
	visible = newVisible;
}
bool UIObject::GetSpanHorizontal()
{
	return spanHorizontal;
}
void UIObject::SetSpanHorizontal(bool newSpanHorizontal)
{
	spanHorizontal = newSpanHorizontal;
}
bool UIObject::GetSpanVertical()
{
	return spanVertical;
}
void UIObject::SetSpanVertical(bool newSpanVertical)
{
	spanVertical = newSpanVertical;
}
vec2 UIObject::GetUsableAreaPos(UIObject* Caller)
{
	return pos;
}
int UIObject::GetUsableAreaWidth(UIObject* Caller)
{
	return width;
}
int UIObject::GetUsableAreaHeight(UIObject* Caller)
{
	return height;
}

void UIObject::Update()
{
	lockHirarchy = false;
	if(Clicked())
	{
		if(hirarchy < Engine->Menu->GetHighestHirarchy())
		{
			SetHirarchy(Engine->Menu->GetHighestHirarchy() +1);
		}
	}
	Show();
}
void UIObject::Show()
{
	if(MouseOver())
	{
		if(Clicked())
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 150,50,50);
		}
		else
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 100,100,100);
		}
	}
	else
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 50,50,50);
	}
}
bool UIObject::MouseOver()
{
	if(this == Engine->Menu->GetTopObjectAtPos(Engine->Input->GetMousePos()))
	{
		return true;
	}
	return false;
}
bool UIObject::Clicked()
{
	if(MouseOver() && Engine->Input->LeftMouse())
	{	
		if(SDL_GetTicks() - timeLastClicked > 200)
		{
			timeLastClicked = SDL_GetTicks();
			return true;
		}
	}
	return false;
}










UIObject* UIElement::GetParent()
{
	return parent;
}
void UIElement::SetParent(UIObject* newParent)
{
	parent = newParent;
}

UIElement::UIElement(LazyEngine* newEngine) : UIObject(newEngine)
{
	parent = NULL;
}
void UIElement::Show()
{
	if(MouseOver())
	{
		if(Clicked())
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 150,50,50);
		}
		else
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 100,150,100);
		}
	}
	else
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 50,100,50);
	}
}
void UIElement::Update()
{
	lockHirarchy = false;
	if(Clicked())
	{
		if(hirarchy < Engine->Menu->GetHighestHirarchy())
		{
			SetHirarchy(Engine->Menu->GetHighestHirarchy() +1);
			if(parent != NULL)
			{
				parent->SetHirarchy(hirarchy - 1);
			}
		}
	}
	
	if(parent != NULL)
	{
		pos = parent->GetUsableAreaPos(this);
		if(spanHorizontal)
		{
			width = parent->GetUsableAreaWidth(this);
		}
		if(spanVertical)
		{
			height = parent->GetUsableAreaHeight(this);
		}
	}
	else
	{
		if(spanHorizontal)
		{
			width = Engine->Graphics->GetHorizontalResolution();
		}
		if(spanVertical)
		{
			height = Engine->Graphics->GetVerticalResolution();
		}
	}
	Show();
}











UIContainer::UIContainer(LazyEngine* newEngine) : UIObject(newEngine)
{
	child = NULL;
}
vec2 UIContainer::GetUsableAreaPos(UIObject* Caller)
{
	return vec2(pos.x + 5, pos.y + 5);
}
int UIContainer::GetUsableAreaWidth(UIObject* Caller)
{
	return width - 10;
}
int UIContainer::GetUsableAreaHeight(UIObject* Caller)
{
	return height - 10;
}
void UIContainer::SetChild(UIElement* newChild)
{
	child = newChild;
	child->SetParent(this);
	child->SetSpanHorizontal(true);
	child->SetSpanVertical(true);
}
void UIContainer::Show()
{
	if(MouseOver())
	{
		if(Clicked())
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 150,50,50);
		}
		else
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 100,100,150);
		}
	}
	else
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 50,50,100);
	}
}
void UIContainer::Update()
{
	lockHirarchy = false;
	if(Clicked())
	{
		if(hirarchy < Engine->Menu->GetHighestHirarchy())
		{
			SetHirarchy(Engine->Menu->GetHighestHirarchy() + 1);
			child->SetHirarchy(hirarchy + 1);
		}
	}
	
	Show();
}









UILabel::UILabel(LazyEngine* newEngine) : UIElement(newEngine)
{
	caption = "default";
}
void UILabel::SetCaption(string newCaption)
{
	caption = newCaption;
}
	
void UILabel::Show()
{
	if(MouseOver())
	{
		if(Clicked())
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 150,50,50);
		}
		else
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 100,100,100);
		}
	}
	else
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 50,50,50);
	}
	Engine->Graphics->DrawRectangleGUI(pos.x, pos.y, width, height, 200,200,200);
	Engine->Graphics->DrawTextGUI(caption, pos.x + 20, pos.y + height/2 - 5);
}
void UILabel::Update()
{
	lockHirarchy = false;
	if(Clicked())
	{
		if(hirarchy < Engine->Menu->GetHighestHirarchy())
		{
			SetHirarchy(Engine->Menu->GetHighestHirarchy() +1);
			if(parent != NULL)
			{
				parent->SetHirarchy(hirarchy - 1);
			}
		}
	}
	
	if(parent != NULL)
	{
		pos = parent->GetUsableAreaPos(this);
		if(spanHorizontal)
		{
			width = parent->GetUsableAreaWidth(this);
		}
		if(spanVertical)
		{
			height = parent->GetUsableAreaHeight(this);
		}
	}
	else
	{
		if(spanHorizontal)
		{
			width = Engine->Graphics->GetHorizontalResolution();
		}
		if(spanVertical)
		{
			height = Engine->Graphics->GetVerticalResolution();
		}
	}
	Show();
}






UIButton::UIButton(LazyEngine* newEngine) : UIElement(newEngine)
{
	caption = "default";
}
void UIButton::SetCaption(string newCaption)
{
	caption = newCaption;
}
	
void UIButton::Show()
{
	if(MouseOver())
	{
		if(Clicked())
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 150,50,50);
		}
		else
		{
			Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 100,100,100);
		}
	}
	else
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 50,50,50);
	}
	Engine->Graphics->DrawRectangleGUI(pos.x, pos.y, width, height, 200,200,200);
	Engine->Graphics->DrawRectangleGUI(pos.x+5, pos.y+5, width-10, height-10, 200,200,200);
	Engine->Graphics->DrawTextGUI(caption, pos.x + 20, pos.y + height/2 - 5);
}
void UIButton::Update()
{
	lockHirarchy = false;
	if(Clicked())
	{
		if(hirarchy < Engine->Menu->GetHighestHirarchy())
		{
			SetHirarchy(Engine->Menu->GetHighestHirarchy() +1);
			if(parent != NULL)
			{
				parent->SetHirarchy(hirarchy - 1);
			}
		}
	}
	
	if(parent != NULL)
	{
		pos = parent->GetUsableAreaPos(this);
		if(spanHorizontal)
		{
			width = parent->GetUsableAreaWidth(this);
		}
		if(spanVertical)
		{
			height = parent->GetUsableAreaHeight(this);
		}
	}
	else
	{
		if(spanHorizontal)
		{
			width = Engine->Graphics->GetHorizontalResolution();
		}
		if(spanVertical)
		{
			height = Engine->Graphics->GetVerticalResolution();
		}
	}
	Show();
}






UIList::UIList(LazyEngine* newEngine) : UIElement(newEngine)
{
}
void UIList::Show()
{
	Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, 50,50,50);
}
void UIList::Update()
{
	lockHirarchy = false;
	if(Clicked())
	{
		if(hirarchy < Engine->Menu->GetHighestHirarchy())
		{
			SetHirarchy(Engine->Menu->GetHighestHirarchy() +1);
			if(parent != NULL)
			{
				parent->SetHirarchy(hirarchy - 1);
			}
			for(unsigned int i = 0; i < childObjects.size(); i++)
			{
				childObjects[i]->SetHirarchy(hirarchy +1);
			}
		}
	}
	
	if(parent != NULL)
	{
		pos = parent->GetUsableAreaPos(this);
		if(spanHorizontal)
		{
			width = parent->GetUsableAreaWidth(this);
		}
		if(spanVertical)
		{
			height = parent->GetUsableAreaHeight(this);
		}
	}
	else
	{
		if(spanHorizontal)
		{
			width = Engine->Graphics->GetHorizontalResolution();
		}
		if(spanVertical)
		{
			height = Engine->Graphics->GetVerticalResolution();
		}
	}
	Show();
}
vec2 UIList::GetUsableAreaPos(UIObject* Caller)
{
	for(unsigned int i = 0; i < childObjects.size(); i++)
	{
		if(Caller == childObjects[i])
		{
			return vec2(pos.x, ((height/childObjects.size())*i)+pos.y);
		}
	}
	return vec2(0,0);
}
int UIList::GetUsableAreaWidth(UIObject* Caller)
{
	return width;
}
int UIList::GetUsableAreaHeight(UIObject* Caller)
{
	return height / childObjects.size();
}
void UIList::AddChild(UIElement* newChildObject)
{
	childObjects.push_back(newChildObject);
	newChildObject->SetParent(this);
	newChildObject->SetSpanHorizontal(true);
	newChildObject->SetSpanVertical(true);
	newChildObject->SetHirarchy(hirarchy + 1);
}
