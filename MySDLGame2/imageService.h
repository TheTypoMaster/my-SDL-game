#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "render.h"
class imageService
{
public:
	imageService();
	bool loadImage(std::string path);//used for permanent images
	SDL_Surface* loadImageReturn(std::string path);//used for images used in one place
	SDL_Surface* loadText(std::string text, SDL_Color colour, int font);
	bool loadFont(std::string path, int size = 10);
	bool isIndexLoaded(int index);
	void getTextSize(int *w, int *h, int font, std::string text);
	~imageService();

	std::vector<SDL_Surface* > surfaces;

	enum commonSurfaces
	{
		//tiles
		missing,
		//entity sprite sheets
		saraSheet,
		//UI
		//	blue
		blue_boxCheckMark,
		blue_boxCross,
		blue_radioButton,
		blue_button1_up,
		blue_button1_down,
		blue_button2_up,
		blue_button2_down,
		blue_button3_up,
		blue_button3_down,
		blue_button4_up,
		blue_button4_down,
		blue_button5_up,
		blue_button5_down,
		blue_button6_up,
		blue_button6_down,
		blue_checkMark,
		blue_circle,
		blue_cross,
		blue_panel,
		blue_sliderDown,
		blue_sliderRight,
		blue_sliderLeft,
		blue_sliderUp,
		//	generic UI
		sliderEnd,
		sliderHorisontal,
		sliderVertical
	};

	enum commonFonts
	{
		UIfont,
		UIfont_thin
	};

	render* globalRenderer;
private:
	int surfacesPointer;
	std::vector<std::string> loadedSurfaces;
	std::vector<TTF_Font* > loadedFonts;
};

