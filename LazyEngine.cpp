#include "LazyEngine.h"

LazyEngine::LazyEngine()
{
	Graphics = new GraphicsEngine;
	Input = new InputEngine;
	quit = false;
}
void LazyEngine::PollEvents()
{
	SDL_Event Event;
	while(SDL_PollEvent(&Event) != 0)
	{
		if(Event.type == SDL_QUIT)
		{
			quit = true;
		}
		else
		{
			Input->getInputEvent(&Event);
		}
	}
}
bool LazyEngine::End()
{
	return quit;
}
void LazyEngine::SetQuit(bool newQuit)
{
	quit = newQuit;
}
