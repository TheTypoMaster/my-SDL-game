#pragma once

#include <vector>
#include "serviceLocator.h"
#include <SDL.h>
#include "button.h"
#include "slider.h"
#include "toolTip.h"
#include "label.h"

class menu
{
public:
	menu(int layout, int w, int h);
	void addButton(int pos);
	void addSlider(int min, int max);
	void addLabel(std::string text, int x, int y);
	void addToolTip(toolTip *newToolTip);
	~menu();

	enum menuLayouts
	{
		list,
		doubleList
	};
protected:
	SDL_Rect menuRect;
	std::vector<button* > buttons;
	std::vector<slider* > sliders;
	std::vector<toolTip* > tooltips;
	std::vector<label* > labels;

	bool setColour(int colour);
};

