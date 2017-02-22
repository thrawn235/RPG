#include "Menu.h"


UIElement::UIElement(MenuHandler* newHandler)
{
	Menu = newHandler;
	Engine = Menu->GetEngine();
	Menu->AddElement(this);
	pos = {0,0};
	width = 200;
	height = 50;
	spanHorizontal = false;
	spanVertical = false;
	active = false; //visible and interactable
	focus = true;
	ParentElement = NULL;
	BorderColor = {255,255,255,255};
	BackgroundColor = {100,100,100,255};
	lastInputTime = 0;
	inputCoolDown = 200;
	Hirarchy = 0;
	ParentElement = NULL;
	LinkParent = NULL;
	LinkedElement = NULL;
}
void UIElement::Update()
{
	if(active)
	{
		Show();
	}
}
void UIElement::Show()
{
	if(MouseOver())
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b);
	}
	else
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, BackgroundColor.r/2, BackgroundColor.g/2, BackgroundColor.b/2);
	}
	if(focus)
	{
		Engine->Graphics->DrawRectangleGUI(pos.x, pos.y, width, height, 200, 0, 0);
	}
	else
	{
		Engine->Graphics->DrawRectangleGUI(pos.x, pos.y, width, height, BorderColor.r, BorderColor.g, BorderColor.b);
	}
}
bool UIElement::MouseOver()
{
	if(Engine->Input->GetMousePos().x >= pos.x && Engine->Input->GetMousePos().y >= pos.y && Engine->Input->GetMousePos().x < pos.x + width && Engine->Input->GetMousePos().y < pos.y + height)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool UIElement::IsActive()
{
	return active;
}
bool UIElement::HasFocus()
{
	return focus;
}
void UIElement::SetSpanHorizontal(bool newSpanHorizontal)
{
	spanHorizontal = newSpanHorizontal;
	if(spanHorizontal)
	{
		if(ParentElement == NULL)
		{
			width = Engine->Graphics->GetHorizontalResolution();
		}
		else
		{
			width = ParentElement->GetWidth() - 6;
		}
	}
}
void UIElement::SetSpanVertical(bool newSpanVertical)
{
	spanVertical = newSpanVertical;
	if(spanVertical)
	{
		if(ParentElement == NULL)
		{
			height = Engine->Graphics->GetVerticalResolution();
		}
		else
		{
			height = ParentElement->GetHeight() - 6;
		}
	}
}
bool UIElement::HasParent()
{
	if(ParentElement == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool UIElement::HasChildren()
{
	return false; //only Lists can have Children
}
bool UIElement::CheckChildrenForFocus()
{
	return false; // Cant have children anyway
}
void UIElement::SetBorderColor(int R, int G, int B, int A)
{
	BorderColor.r = R;
	BorderColor.g = G;
	BorderColor.b = B;
	BorderColor.a = A;
}
void UIElement::SetBackgroundColor(int R, int G, int B, int A)
{
	BackgroundColor.r = R;
	BackgroundColor.g = G;
	BackgroundColor.b = B;
	BackgroundColor.a = A;
}
bool UIElement::Clicked()
{
	if(MouseOver() && Engine->Input->LeftMouse() && IsActive())
	{
		if(!CoolingDown())
		{
			return true;
		}
	}
	return false;
}
bool UIElement::CoolingDown()
{
	if(SDL_GetTicks() - lastInputTime > inputCoolDown)
	{
		return false; //ready for Input
	}
	else
	{
		return true; //still blocked
	}
}
void UIElement::SetActive(bool newActive)
{
	active = newActive;
	if(active)
	{
		Menu->SetHirarchyForAll(0);
		SetHirarchy(5);
		if(ParentElement != NULL)
		{
			ParentElement->SetHirarchy(5);
		}
	}
	
}
void UIElement::SetFocus(bool newFocus)
{
	//only one element can have focus
	focus = newFocus; 
	if(focus)
	{
		if(ParentElement != NULL)
		{
			ParentElement->SetFocus(false);
		}
		//Set Chilidren to not focus, but only lists have children
	}
}
void UIElement::SetPosToMousePos()
{
	pos = Engine->Input->GetMousePos();
}
void UIElement::SetPos(vec2 newPos)
{
	pos = newPos;
}
vec2 UIElement::GetPos()
{
	return pos;
}
int UIElement::GetWidth()
{
	return width;
}
int UIElement::GetHeight()
{
	return height;
}
void UIElement::SetWidth(int newWidth)
{
	width = newWidth;
	spanHorizontal = false;
}
void UIElement::SetHeight(int newHeight)
{
	height = newHeight;
	spanVertical = false;
}
void UIElement::SetParentElement(UIElement* newParent)
{
	ParentElement = newParent;
}
void UIElement::SetHirarchy(int newHirarchy)
{
	Hirarchy = newHirarchy;
}
int UIElement::GetHirarchy()
{
	return Hirarchy;
}
void UIElement::SetLinkParent(UIElement* newLinkParent)
{
	LinkParent = newLinkParent;
}
UIElement* UIElement::GetLinkParent()
{
	return LinkParent;
}
void UIElement::SetLinkedElement(UIElement* newLinkedElement)
{
	LinkedElement = newLinkedElement;
}
UIElement* UIElement::GetLinkedElement()
{
	return LinkedElement;
}
UIElement* UIElement::GetParentElement()
{
	return ParentElement;
}













VerticalList::VerticalList(MenuHandler* newHandler) : UIElement(newHandler)
{
	
}
void VerticalList::Attach(UIElement* newElement)
{
	ChildElements.push_back(newElement);
	newElement->SetPos(vec2(pos.x+3, pos.y+HeightOfAllChildren()-newElement->GetHeight()));
	newElement->SetParentElement(this);
	newElement->SetSpanHorizontal(true);
	height = HeightOfAllChildren();
	cout<<newElement->GetHirarchy()<<endl;
}
void VerticalList::Clear()
{
	ChildElements.clear();
}
int VerticalList::GetWidestChildWidth()
{
	int widest = 0;
	for(unsigned int i = 0; i < ChildElements.size(); i++)
	{
		if(ChildElements[i]->GetWidth() > widest)
		{
			widest = ChildElements[i]->GetWidth();
		}
	}
	return widest;
}
bool VerticalList::HasChildren()
{
	if(ChildElements.size() > 0)
	{
		return true;
	}
	return false;
}
bool VerticalList::CheckChildrenForFocus()
{
	for(unsigned int i = 0; i <= ChildElements.size(); i++)
	{
		if(ChildElements[i]->HasFocus() == true)
		{
			return true;
		}
	}
	return false;
}
void VerticalList::SetFocus(bool newFocus)
{
	//only one element can have focus
	focus = newFocus; 
	if(focus)
	{
		if(ParentElement != NULL)
		{
			ParentElement->SetFocus(false);
		}
		for(unsigned int i = 0; i < ChildElements.size(); i++)
		{
			ChildElements[i]->SetFocus(false);
		}
	}
}
int VerticalList::HeightOfAllChildren()
{
	int totalHeight = 0;
	for(unsigned int i = 0; i < ChildElements.size(); i++)
	{
		totalHeight = totalHeight + ChildElements[i]->GetHeight();
	}
	return totalHeight;
}
void VerticalList::SetHeightOfChildren(int newHeight)
{
	for(unsigned int i = 0; i < ChildElements.size(); i++)
	{
		ChildElements[i]->SetHeight(newHeight);
		ChildElements[i]->SetPos(vec2(pos.x, pos.y+newHeight*i));
	}
	height = HeightOfAllChildren();
}
void VerticalList::SetPosToMousePos()
{
	pos = Engine->Input->GetMousePos();
	RefreshChildPos();
	
}
void VerticalList::SetPos(vec2 newPos)
{
	pos = newPos;
	RefreshChildPos();
}
void VerticalList::RefreshChildPos()
{
	for(unsigned int i = 0; i < ChildElements.size(); i++)
	{
		int currentHeight = 0;
		for(unsigned int u = 0; u < i; u++)
		{
			currentHeight = currentHeight + ChildElements[u]->GetHeight();
		}
		ChildElements[i]->SetPos(vec2(pos.x+3, pos.y+currentHeight));
	}
}
void VerticalList::SetActive(bool newActive)
{
	active = newActive;
	if(active)
	{
		Menu->SetHirarchyForAll(0);
		SetHirarchy(5);
		if(ParentElement != NULL)
		{
			ParentElement->SetHirarchy(5);
		}
		for(unsigned int i = 0; i < ChildElements.size(); i++)
		{
			ChildElements[i]->SetActive(true);
			ChildElements[i]->SetHirarchy(6);
			cout<<" My Hirarchy is "<<GetHirarchy()<<" and my sons is "<<ChildElements[i]->GetHirarchy()<<endl;
		}
	}
	
}










Button::Button(MenuHandler* newHandler) : UIElement(newHandler)
{
	Caption = "empty";
	TextColor = {255,255,255,255};
	linkedElement = NULL;
}
void Button::Update()
{
	if(active)
	{
		Show();
		if(linkedElement != NULL)
		{
			if(Clicked())
			{
				SetFocus(false);
				linkedElement->SetActive(true);
				linkedElement->SetFocus(true);
				linkedElement->SetPosToMousePos();
			}
		}
	}
}
void Button::SetTextColor(int R, int G, int B, int A)
{
	TextColor.r = R;
	TextColor.g = G;
	TextColor.b = B;
	TextColor.a = A;
}
void Button::SetCaption(string newCaption)
{
	Caption = newCaption;
}
void Button::Attach(UIElement* newElement)
{
	linkedElement = newElement;
	linkedElement->SetLinkParent(this);
}
void Button::Show()
{
	if(MouseOver())
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b);
	}
	else
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, BackgroundColor.r/2, BackgroundColor.g/2, BackgroundColor.b/2);
	}
	if(focus)
	{
		Engine->Graphics->DrawRectangleGUI(pos.x, pos.y, width, height, 200, 0, 0);
	}
	else
	{
		Engine->Graphics->DrawRectangleGUI(pos.x, pos.y, width, height, BorderColor.r, BorderColor.g, BorderColor.b);
	}
	Engine->Graphics->DrawRectangleGUI(pos.x+5, pos.y+5, width-10, height-10, BorderColor.r, BorderColor.g, BorderColor.b);
	Engine->Graphics->DrawTextGUI(Caption, pos.x + 10, pos.y + height/2 - 4);
}
bool Button::Clicked()
{
	if(MouseOver() && Engine->Input->LeftMouse() && IsActive())
	{
		if(!CoolingDown())
		{
			return true;
		}
	}
	return false;
}











Label::Label(MenuHandler* newHandler) : UIElement(newHandler)
{
	Caption = "empty";
	TextColor = {255,255,255,255};
}
void Label::SetTextColor(int R, int G, int B, int A)
{
	TextColor.r = R;
	TextColor.g = G;
	TextColor.b = B;
	TextColor.a = A;
}
void Label::SetCaption(string newCaption)
{
	Caption = newCaption;
}
void Label::Show()
{
	if(MouseOver())
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, BackgroundColor.r, BackgroundColor.g, BackgroundColor.b);
	}
	else
	{
		Engine->Graphics->DrawFilledRectangleGUI(pos.x, pos.y, width, height, BackgroundColor.r/2, BackgroundColor.g/2, BackgroundColor.b/2);
	}
	if(focus)
	{
		Engine->Graphics->DrawRectangleGUI(pos.x, pos.y, width, height, 200, 0, 0);
	}
	else
	{
		Engine->Graphics->DrawRectangleGUI(pos.x, pos.y, width, height, BorderColor.r, BorderColor.g, BorderColor.b);
	}
	Engine->Graphics->DrawTextGUI(Caption, pos.x + 10, pos.y + height/2 - 4);
}

class Entry : protected UIElement
{
	protected:
	int CursorPos;
	string InputString;
	
	public:
	Entry(LazyEngine* newEngine);
	virtual void Update();
	virtual void Show();
};






















MenuHandler::MenuHandler(LazyEngine* newEngine)
{
	Engine = newEngine;
}
void MenuHandler::Update()
{
	for(int u = 0; u < 20; u++)
	{
		for(unsigned int i = 0; i < Elements.size(); i++)
		{
			if(Elements[i]->GetHirarchy() == u)
			{
				Elements[i]->Update();
			}
		}
	}
}
void MenuHandler::AddElement(UIElement* newElement)
{
	Elements.push_back(newElement);
	cout<<"I know "<<Elements.size()<<" Elements"<<endl;
}
LazyEngine* MenuHandler::GetEngine()
{
	return Engine;
}
void MenuHandler::SetHirarchyForAll(int newHirarchy)
{
	for(unsigned int i = 0; i < Elements.size(); i++)
	{
		Elements[i]->SetHirarchy(0);
	}
}
