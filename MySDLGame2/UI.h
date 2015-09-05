#pragma once
#include "inventoryDisplay.h"
#include "serviceLocator.h"
#include "button.h"
#include "menu.h"
#include "slider.h"
#include "toolTip.h"
#include "inventoryDisplay.h"
#include <vector>
class UI
{
public:
	UI(serviceLocator* SL);
	void update();
	void eventUpdate();
	void draw();
	button* registerButton();
	label* registerLabel();
	slider* registerSlider();
	bool changeColour(int newColour);
	~UI();

	enum colours
	{
		grey,
		blue,
		green,
		red,
		yellow
	};

private:
	serviceLocator* mySL;
	int colour;

	std::vector<button* > buttons;
	std::vector<label* > labels;
	std::vector<slider* > sliders;

	int buttonCount, labelCount, sliderCount;
};

