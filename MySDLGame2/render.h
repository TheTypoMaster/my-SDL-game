#pragma once
#include <SDL.h>
class render
{
public:
	render();
	bool init();
	bool drawScreen();
	bool drawSurface(SDL_Surface* surface, SDL_Rect rect);
	bool drawScaledSurface(SDL_Surface* surface, SDL_Rect rect);
	bool drawTexture(SDL_Texture* texture);
	bool drawScaledViewportSurface(SDL_Surface* surface, SDL_Rect strechRect, SDL_Rect viewport);
	bool drawViewportSurface(SDL_Surface* surface, SDL_Rect viewport, SDL_Rect rect);
	int const screenWidth = 640;
	int const screenHeight = 480;
	int xOffset, yOffset;
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	~render();
private:

};

