#include "entityService.h"


entityService::entityService(serviceLocator* SL)
	:mySL(SL)
{
}

void entityService::update()
{

}

void entityService::draw()
{

}

int entityService::detectCollision(entity* entity1, entity* entity2)
{
	return 0;
}

int entityService::detectCollision(entity* ent, block* blk)
{
	return 0;
}

entityService::~entityService()
{
}
