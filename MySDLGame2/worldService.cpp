#include "worldService.h"


worldService::worldService()
{
}

bool worldService::getNewWorld(serviceLocator* SL)
{
	world tempWorld(SL);
	worlds.push_back(tempWorld);
	return true;
}

worldService::~worldService()
{
}
