#pragma once
#include "serviceLocator.h"
#include "label.h"
class button
{
public:
	button(serviceLocator* SL);
	bool setType(int newType);
	void draw();
	void update();
	void onClick();
	void onMouseDown();
	void onMouseUp();
	void eventUpdate();
	void setSize(int w, int h);
	void setPos(int x, int y);
	void setText(std::string text);
	bool getState();
	void disable();
	void enable();
	~button();

	bool enabled;
	bool clicked;

	enum type
	{
		type1,
		type2,
		type3,
		type4,
		type5,
		type6
	};
private:
	int type;
	int up, down;
	
	SDL_Rect buttonRect;
	label buttonText;
	serviceLocator* mySL;

	bool state;
};

