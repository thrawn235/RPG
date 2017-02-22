#include "Graphics.h" 

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
