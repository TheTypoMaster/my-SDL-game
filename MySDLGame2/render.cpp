#include "render.h"
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <iostream>

render::render()
{
}

bool render::init()
{
	xOffset = 0;
	yOffset = 0;
	//create the window
	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL) // if the window wasn't created
	{
		std::cout << "[ERROR]: An error occured in a 'render' class. SDL error " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		// get the screen's surface
		screenSurface = SDL_GetWindowSurface(window);
		if (screenSurface == NULL) // if the surface wasn't gotten
		{
			std::cout << "[ERROR]: an error occured while trying to get the window surface. SDL error " << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			std::cout << "[INFO]: The renderer was successfully initialised" << std::endl;
			return true;
		}
	}
}

bool render::drawScreen()
{
	

	if (SDL_UpdateWindowSurface(window) != 0) // draw the surface to the window
	{
		std::cout << "[ERROR]: the window wasn't updated SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00)); // clear the screen surface
	return true;
}

bool render::drawSurface(SDL_Surface* surface, SDL_Rect rect)
{
	if (SDL_BlitSurface(surface, NULL, screenSurface, &rect) != 0)// draw the surface directly to the screen surface
	{
		std::cout << "[ERROR]: the surface couldn't be blitted SDL_Error: " << SDL_GetError() << std::endl;
		
		return false;
	}

	if (surface == NULL)
	{
		std::cout << "[ERROR]: the surface passed was NULL" << std::endl;
		return false;
	}
	return true;
}

bool render::drawScaledSurface(SDL_Surface* surface, SDL_Rect rect)
{
	if (SDL_BlitScaled(surface, NULL, screenSurface, &rect))// draw the surface to the screen to the size of the rectangle
	{
		std::cout << "[ERROR]: the surface couldn't be scale-blitted" << std::endl;
		return false;
	}

	if (surface == NULL)
	{
		std::cout << "[ERROR]: the surface passed was NULL" << std::endl;
		return false;
	}
	return true;
}

bool render::drawScaledViewportSurface(SDL_Surface* surface, SDL_Rect strechRect, SDL_Rect viewport)
{
	SDL_BlitScaled(surface, &viewport, screenSurface, &strechRect); // draw a section of the surface to the screen to the size of the rectangle
	return true;
}

bool render::drawViewportSurface(SDL_Surface* surface, SDL_Rect viewport, SDL_Rect rect)
{
	SDL_BlitSurface(surface, &viewport, screenSurface, &rect); // draw a section of the surface directly to the screen surface
	return true;
}

bool render::drawTexture(SDL_Texture* texture)
{
	return false;
}


render::~render()
{
	// destroy the window and NULL the pointer
	SDL_DestroyWindow(window);
	window = NULL;
}
