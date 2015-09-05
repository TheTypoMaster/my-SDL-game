#pragma once
#include "serviceLocator.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "label.h"
#include <vector>
class toolTip
{
public:
	toolTip(serviceLocator* SL);
	void update();
	void eventUpdate();
	void draw();
	void setTitle(std::string newTitle);
	void setBody(std::string newBody);
	void setFlavorText(std::string newFlavorText);
	void setAttribute(std::string attributeText);
	void setupTooltip();
	~toolTip();

	bool enabled;


private:
	serviceLocator* mySL;

	std::vector<std::string> wrapText(std::string text);

	SDL_Rect drawRect;
	SDL_Rect backgroundRect;

	std::string titleString;
	std::vector<std::string> bodyStrings;
	std::vector<std::string> flavorTextString;
	std::vector<std::string> attributeString;

	SDL_Surface* tooltipSurface;
	SDL_Surface* titleSurface;
	std::vector<SDL_Surface* > bodySurfaces;
	std::vector<SDL_Surface* > flavorTextSurfaces;
	std::vector<SDL_Surface* > attributeSurfaces;

	const int maxWidth = 150;
	const int maxHeight = 150;
	const int lineSpacing = 0;

	const int sectionBuffer = 3;
	const int widthBuffer = 15;
	const int heightBuffer = 3;

	bool setup;

	void getMaxWidth();
	void getMaxHeight();

	Uint32 rmask, gmask, bmask, amask;
};

