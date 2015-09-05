#pragma once
#include "serviceLocator.h"
class item
{
public:
	item();
	virtual void onRightClick();
	virtual void onLeftClick();
	virtual void onDrop();
	virtual void update();
	virtual void draw();
	bool setSL(serviceLocator* SL);
	~item();

	int type;
	int maxStack;
	int damageState;
protected:
	serviceLocator* mySL;
};

