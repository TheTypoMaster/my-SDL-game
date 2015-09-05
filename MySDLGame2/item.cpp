#include "item.h"


item::item()
{
}

void item::onDrop()
{

}

void item::onLeftClick()
{

}

void item::onRightClick()
{

}

void item::update()
{

}

void item::draw()
{

}

bool item::setSL(serviceLocator* SL)
{
	if (SL == NULL)
	{
		return false;
	}

	mySL = SL;

	if (mySL == NULL)
	{
		return false;
	}

	return true;
}

item::~item()
{
}
