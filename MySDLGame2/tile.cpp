#include "tile.h"
#include <iostream>

tile::tile(serviceLocator* SL)
	:mySL(SL)
{
	boundingRect = { 0, 0, 0, 0 };
}

void tile::update()
{
}

void tile::draw(int x, int y)
{
	SDL_Rect drawRect;
	drawRect.x = x;
	drawRect.y = y;

	drawRect.x += mySL->globalRenderer.xOffset;
	drawRect.y += mySL->globalRenderer.yOffset;
	
	mySL->globalRenderer.drawSurface(surface, drawRect);
}

bool tile::loadSurface(std::string path)
{
	surface = mySL->myImageService.loadImageReturn(path);
	if (surface != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void tile::setID(int ID)
{
	tileID = ID;
}

tile::~tile()
{
}