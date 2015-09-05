#pragma once
#include "serviceLocator.h"
class label
{
public:
	label(serviceLocator* SL);
	bool changeText(std::string text, SDL_Color colour);
	void draw();
	void setPos(int x, int y = -1);
	void modSize(int mod);
	void setSize(int w, int h);
	void centerOn(SDL_Rect centerRect);
	~label();

	SDL_Rect labelRect;

	bool enabled;
private:
	SDL_Surface* labelSurface;
	serviceLocator* mySL;
	
};