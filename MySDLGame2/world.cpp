#include "world.h"


world::world(serviceLocator* SL)
{
	mySL = SL;
	mainWorld.setServiceLocator(mySL);
}

bool world::getNewGrid()
{
	worldGrid tempGrid(mySL);
	otherGrids.push_back(tempGrid);
	return true;
}

bool world::getNewWorldGrid()
{
	worldGrid tempGrid(mySL);
	mainWorld = tempGrid;
	return true;
}

void world::drawCurrentGrid()
{
	if (currentGrid == -1)
	{
		mainWorld.draw();
	}
	else
	{
		otherGrids[currentGrid].draw();
	}
}

world::~world()
{
}
