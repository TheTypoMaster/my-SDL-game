#include "UI.h"


UI::UI(serviceLocator* SL)
	:mySL(SL)
{
}

button* UI::registerButton()
{
	button* newButton = new button(mySL);
	buttons.push_back(newButton);
	buttonCount++;
	return buttons.back();
}

label* UI::registerLabel()
{
	label* newLabel = new label(mySL);
	labels.push_back(newLabel);
	labelCount++;
	return labels.back();
}

slider* UI::registerSlider()
{
	slider* newSlider = new slider(mySL);
	sliders.push_back(newSlider);
	sliderCount++;
	return sliders.back();
}

void UI::update()
{
	for (int i = 0; i < buttonCount; i++)
	{
		buttons[i]->update();
	}

	for (int i = 0; i < sliderCount; i++)
	{
		sliders[i]->update();
	}
}

void UI::eventUpdate()
{
	for (int i = 0; i < buttonCount; i++)
	{
		buttons[i]->eventUpdate();
	}

	for (int i = 0; i < sliderCount; i++)
	{
		sliders[i]->eventUpdate();
	}
}

void UI::draw()
{
	for (int i = 0; i < buttonCount; i++)
	{
		buttons[i]->draw();
	}

	for (int i = 0; i < labelCount; i++)
	{
		labels[i]->draw();
	}

	for (int i = 0; i < sliderCount; i++)
	{
		sliders[i]->draw();
	}
}

UI::~UI()
{
}
