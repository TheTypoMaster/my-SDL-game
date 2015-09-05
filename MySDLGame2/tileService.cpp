#include "tileService.h"


tileService::tileService(serviceLocator* SL)
	:mySL(SL)
{
}

void tileService::update()
{
	for (int i = 0; i < int(updates.size()); i++)
	{
		updates[i]->update();
	}
}

int tileService::registerTile(tile* newTile)
{
	tiles.push_back(newTile);
	newTile->setID(int(tiles.size()));
	return int(tiles.size());
}

bool tileService::registerForUpdtaes(tile* newTile)
{
	if (newTile != NULL)
	{
		updates.push_back(newTile);
		return true;
	}
	else
	{
		return false;
	}
}

tileService::~tileService()
{
}
