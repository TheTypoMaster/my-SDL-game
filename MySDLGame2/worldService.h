#pragma once
#include "world.h"
#include <vector>
#include <string>

class worldService
{
public:
	worldService();
	bool getNewWorld(serviceLocator* SL);
	bool loadWorld();
	~worldService();

	std::vector<world> worlds;
	int currentWorld;
private:
};

