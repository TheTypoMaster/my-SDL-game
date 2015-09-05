#include "imageService.h"
#include <iostream>


imageService::imageService()
{
}

bool imageService::loadImage(std::string path)
{

	if (globalRenderer == NULL)
	{
		std::cout << "[ERROR]: the global renderer pointer is NULL. image service can't load textures" << std::endl;
		return false;
	}
	//check if the image has already been loaded
	for (int i = 0; i < surfacesPointer; i++)
	{
		if (loadedSurfaces[i] == path)
		{
			std::cout << "[WARN]: The image \"" << path << "\" has already been registered." << std::endl;
			return false;
		}

		if (surfaces[i] == NULL)//check if the surface has something loaded (it should have something loaded - 0 to last loaded image)
		{
			std::cout << "[ERROR]: The image at index "<< i << " is NULL" << std::endl;
			return false;
		}
	}

	SDL_Surface* surface = IMG_Load(path.c_str());//load the image to the surface

	if (surface == NULL)
	{
		std::cout << "[ERROR]: The path at " << path.c_str() << "couldn't be loaded SDL_ERROR" << SDL_GetError() << std::endl;
		return false;
	}

	surface = SDL_ConvertSurface(surface, globalRenderer->screenSurface->format, NULL);//optimise the surface

	surfaces.push_back(surface);//add the surface to the vector
	//check if the image was actually loaded
	if (surfaces[surfacesPointer] != NULL)
	{
		std::cout << "[INFO]: The image \"" << path << "\" was loaded at position " << surfacesPointer << std::endl;
		loadedSurfaces.push_back(path);
		surfacesPointer++;
		return true;
	}
	std::cout << "[ERROR]: the surface at " << surfacesPointer << " was NULL";
	return false;
}

SDL_Surface* imageService::loadImageReturn(std::string path)
{

	if (globalRenderer == NULL)
	{
		std::cout << "[ERROR]: the global renderer pointer is NULL. image service can't load textures" << std::endl;
		return NULL;
	}

	SDL_Surface* surface = IMG_Load(path.c_str());//load the image to the surface

	if (surface == NULL)
	{
		std::cout << "[ERROR]: The path at " << path << "couldn't be loaded SDL_ERROR" << SDL_GetError() << std::endl;
		return NULL;
	}

	surface = SDL_ConvertSurface(surface, globalRenderer->screenSurface->format, NULL);//optimise the surface

	if (surface != NULL)
	{
		std::cout << "[INFO]: The image \"" << path << "\" was loaded" << std::endl;
		return surface;
	}
	std::cout << "[ERROR]: the surface loaded with \"" << path << "\" was NULL";
	return NULL;
}

SDL_Surface* imageService::loadText(std::string text, SDL_Color colour, int font)
{
	SDL_Surface* textSurface;
	textSurface = TTF_RenderText_Solid(loadedFonts[font], text.c_str(), colour);
	if (textSurface == NULL)
	{
		std::cout << "[ERROR]: couldn't make text surface\"" << text << "\" with font " << font << ". SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_ConvertSurface(textSurface, globalRenderer->screenSurface->format, NULL);//optimise the surface

	return textSurface;
}

bool imageService::loadFont(std::string path, int size)
{
	loadedFonts.push_back(TTF_OpenFont(path.c_str(), size));
	if (loadedFonts.back() == NULL)
	{
		std::cout << "[ERROR]: Couldn't load font \"" << path << "\". SDL_ERROR: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

bool imageService::isIndexLoaded(int index)
{
	if (surfaces[index] == NULL)
	{
		return false;
	}
	return true;
}

void imageService::getTextSize(int *w, int *h, int font, std::string text)
{
	TTF_SizeText(loadedFonts[font], text.c_str(), w, h);
}


	imageService::~imageService()
{
}
