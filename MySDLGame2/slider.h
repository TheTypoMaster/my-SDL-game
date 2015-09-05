#pragma once
#include "serviceLocator.h"
#include <SDL.h>
#include "label.h"
class slider
{
public:
	slider(serviceLocator* SL);
	void eventUpdate();
	void update();
	void draw();
	int getValue();
	void setPos(int x, int y);
	void setWidth(int w);
	void setSliderPos(int x);
	//void setSliderSize(int w, int h);
	void setDirection(int direction);
	void setBounds(int min, int max);
	~slider();

	enum direction
	{
		up,
		down,
		left,
		right
	};

	bool valueChanged;
	bool enabled;
private:
	void updatePP();
	void updateStep();

	SDL_Rect sliderTrackRect, sliderEndRect;
	SDL_Rect sliderRect;
	int minValue, maxValue;
	int direction;
	int step, value;
	bool stepPerPixel;
	serviceLocator* mySL;
	bool clicked;
	SDL_Rect stepRect;
};

