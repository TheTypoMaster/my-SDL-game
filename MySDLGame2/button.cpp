#include "button.h"


button::button(serviceLocator* SL)
	:mySL(SL),
	buttonText(SL),
	enabled(true)
{
	setType(type1);
}

void button::setText(std::string text)
{
	SDL_Color colour;
	colour.r = colour.g = colour.b = 0xff;
	buttonText.changeText(text, colour);
	buttonText.centerOn(buttonRect);
}

void button::setPos(int x, int y)
{
	buttonRect.x = x;
	buttonRect.y = y;
}

void button::setSize(int w, int h)
{
	buttonRect.w = w;
	buttonRect.h = h;
}

void button::update()
{

}

void button::eventUpdate()
{
	if (enabled)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (mySL->currentEvent.type == SDL_MOUSEBUTTONDOWN)
		{
			if (x > buttonRect.x && x < buttonRect.w + buttonRect.x)
			{
				if (y > buttonRect.y && y < buttonRect.h + buttonRect.y)
				{
					clicked = true;
					buttonRect.y += 3;
					buttonRect.h -= 3;
					buttonText.labelRect.y += 3;
				}
			}
		}

		if (mySL->currentEvent.type == SDL_MOUSEBUTTONUP && clicked)
		{
			clicked = false;
			buttonRect.y -= 3;
			buttonRect.h += 3;
			buttonText.labelRect.y -= 3;
			state = true;
		}
	}
}

bool button::getState()
{
	if (state)
	{
		state = false;
		return true;
	}
	
	return false;
}

void button::disable()
{
	enabled = false;
}

void button::enable()
{
	enabled = true;
}

void button::draw()
{
	if (enabled)
	{
		if (!clicked)
		{
			mySL->globalRenderer.drawScaledSurface(mySL->myImageService.surfaces[up], buttonRect);
			buttonText.draw();
		}
		else
		{
			mySL->globalRenderer.drawScaledSurface(mySL->myImageService.surfaces[down], buttonRect);
			buttonText.draw();
		}
	}
}

bool button::setType(int newType)
{
	type = newType;
	switch (type)
	{
	case type1:
		up = mySL->myImageService.blue_button1_up;
		down = mySL->myImageService.blue_button1_down;
		break;
	case type2:
		up = mySL->myImageService.blue_button2_up;
		down = mySL->myImageService.blue_button2_down;
		break;
	case type3:
		up = mySL->myImageService.blue_button3_up;
		down = mySL->myImageService.blue_button3_down;
		break;
	case type4:
		up = mySL->myImageService.blue_button4_up;
		down = mySL->myImageService.blue_button4_down;
		break;
	case type5:
		up = mySL->myImageService.blue_button5_up;
		down = mySL->myImageService.blue_button5_down;
		break;
	case type6:
		up = mySL->myImageService.blue_button6_up;
		down = mySL->myImageService.blue_button6_down;
		break;
	default:
		return false;
	}

	return true;
}

button::~button()
{
}
