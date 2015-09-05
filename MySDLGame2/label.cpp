#include "label.h"


label::label(serviceLocator* SL)
	:mySL(SL),
	enabled(true)
{
}

void label::draw()
{
	if (enabled)
		mySL->globalRenderer.drawSurface(labelSurface, labelRect);
}

void label::setPos(int x, int y)
{
	if (x != -1)
		labelRect.x = x;
	if (y != - 1)
		labelRect.y = y;
}

bool label::changeText(std::string text, SDL_Color colour)
{
	labelSurface = mySL->myImageService.loadText(text, colour, mySL->myImageService.UIfont);
	if (labelSurface == NULL)
		return false;

	labelRect.w = labelSurface->w;
	labelRect.h = labelSurface->h;

	return true;
}

void label::modSize(int mod)
{
	labelRect.w = labelSurface->w * mod;
	labelRect.h = labelSurface->h * mod;
}

void label::setSize(int w, int h)
{
	labelRect.w = w;
	labelRect.h = h;
}

void label::centerOn(SDL_Rect centerRect)
{
	labelRect.x = centerRect.x + ((centerRect.w / 2) - (labelRect.w / 2));
	labelRect.y = centerRect.y + ((centerRect.h / 2) - (labelRect.h / 2));
}

label::~label()
{
}
