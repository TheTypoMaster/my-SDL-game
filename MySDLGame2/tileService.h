#pragma once
#include "serviceLocator.h"
#include "tile.h"
#include <vector>
class tileService
{
public:
	tileService(serviceLocator* SL);
	void update();
	int registerTile(tile* newTile);
	bool registerForUpdtaes(tile* newTile);// for animation updates
	~tileService();

	std::vector<tile* > tiles;

private:
	std::vector<tile* > updates;
	serviceLocator* mySL;
};

