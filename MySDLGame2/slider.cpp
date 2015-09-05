#include "slider.h"


slider::slider(serviceLocator* SL)
	:mySL(SL),
	direction(up),
	enabled(true)
{
	
	sliderEndRect.w = mySL->myImageService.surfaces[mySL->myImageService.sliderEnd]->w;
	sliderRect.w = mySL->myImageService.surfaces[mySL->myImageService.blue_sliderUp]->w;
	sliderRect.h = mySL->myImageService.surfaces[mySL->myImageService.blue_sliderUp]->h;
	sliderTrackRect.w = 100 + sliderRect.w;
	sliderTrackRect.h = mySL->myImageService.surfaces[mySL->myImageService.sliderHorisontal]->h;
}

void slider::update()
{
	if (stepPerPixel)
	{
		updatePP();
	}
	else
	{
		updateStep();
	}
}

void slider::updateStep()
{
	int x;
	SDL_GetRelativeMouseState(&x, NULL);
	int x2;
	SDL_GetMouseState(&x2, NULL);

	if (clicked && enabled)
	{
		if (x2 - sliderRect.x > 0)
		{
			//if the mouse is further right
			if (x2 - sliderRect.x > step && (sliderRect.x + sliderRect.w) + step <= sliderTrackRect.x + sliderTrackRect.w)
			{
				sliderRect.x += step;
				value += 1;
			}
		}
		else
		{
			//if the mouse is further left
			if (sliderRect.x - x2 > step && sliderRect.x - step >= sliderTrackRect.x)
			{
				sliderRect.x -= step;
				value -= 1;
			}
		}
	
		
	}
}

void slider::updatePP()
{
	int x;
	SDL_GetRelativeMouseState(&x, NULL);
	int x2;
	SDL_GetMouseState(&x2, NULL);

	if (clicked && enabled)
	{
		if (x2 >= sliderTrackRect.x && x2 <= sliderTrackRect.x + sliderTrackRect.w)
		{
			sliderRect.x += x;

			if (sliderRect.x < sliderTrackRect.x)
			{
				sliderRect.x = sliderTrackRect.x;
			}

			if (sliderRect.x + sliderRect.w > sliderTrackRect.x + sliderTrackRect.w)
			{
				sliderRect.x = (sliderTrackRect.x + sliderTrackRect.w) - sliderRect.w;
			}

			value += x * step;

			if (value < minValue)
			{
				value = minValue;
			}

			if (value > maxValue)
			{
				value = maxValue;
			}
		}

	}
}

void slider::eventUpdate()
{
	if (enabled)
	{
		if (mySL->currentEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (x > sliderRect.x && x < sliderRect.x + sliderRect.w)
			{
				if (y > sliderRect.y && y < sliderRect.y + sliderRect.h)
				{
					clicked = true;
				}
			}
		}

		if (mySL->currentEvent.type == SDL_MOUSEBUTTONUP)
		{
			clicked = false;
		}
	}
}

void slider::draw()
{
	if (enabled)
	{
		switch (direction)
		{
		case up:
			sliderEndRect.x = sliderTrackRect.x - sliderEndRect.w;
			mySL->globalRenderer.drawSurface(mySL->myImageService.surfaces[mySL->myImageService.sliderEnd], sliderEndRect);
			sliderEndRect.x = sliderTrackRect.x + sliderTrackRect.w;
			mySL->globalRenderer.drawSurface(mySL->myImageService.surfaces[mySL->myImageService.sliderEnd], sliderEndRect);

			mySL->globalRenderer.drawScaledSurface(mySL->myImageService.surfaces[mySL->myImageService.sliderHorisontal], sliderTrackRect);

			mySL->globalRenderer.drawSurface(mySL->myImageService.surfaces[mySL->myImageService.blue_sliderUp], sliderRect);
			break;
		case down:
			break;
		}
		SDL_FillRect(mySL->globalRenderer.screenSurface, &stepRect, SDL_MapRGB(mySL->globalRenderer.screenSurface->format, 255, 255, 255));
	}
}

int slider::getValue()
{
	return value;
}

void slider::setBounds(int min, int max)
{
	minValue = min;
	maxValue = max;

	if (sliderTrackRect.w - sliderRect.w < maxValue)
	{
		step = (maxValue - minValue) / (sliderTrackRect.w - sliderRect.w);
		stepPerPixel = true;
	}

	if (sliderTrackRect.w - sliderRect.w > maxValue)
	{
		stepPerPixel = false;
		step = (sliderTrackRect.w - sliderRect.w) / (maxValue - minValue);
		stepRect.w = (sliderTrackRect.w - sliderRect.w) / step;
	}

	if (sliderTrackRect.w - sliderRect.w == maxValue)
	{
		stepPerPixel = true;
		step = 1;
	}
}

void slider::setPos(int x, int y)
{
	sliderRect.x = (sliderRect.x - sliderTrackRect.x) + x;
	sliderTrackRect.x = x;
	sliderTrackRect.y = y;

	stepRect.x = x;

	switch (direction)
	{
	case up:
		sliderRect.y = y - 24;
		sliderEndRect.x = sliderTrackRect.x - sliderEndRect.w;
		sliderEndRect.y = y - 3;
		break;
	case down:

		sliderEndRect.x = sliderTrackRect.x - sliderEndRect.w;
		sliderEndRect.y = y - 3;
		break;
	}
}

void slider::setSliderPos(int x)
{
	/*sliderRect.x = sliderTrackRect.x + x;*/
}

void slider::setWidth(int w)
{
	sliderTrackRect.w = w;

	if (w < maxValue)
	{
		step = maxValue / w;
	}

	if (w > maxValue)
	{
		step = w / maxValue;
	}

	if (w == maxValue)
	{
		step = 1;
	}
}

slider::~slider()
{
}
