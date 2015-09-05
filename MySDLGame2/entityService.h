#pragma once
#include "entity.h"
#include "chunk.h"
#include "block.h"
#include "tile.h"
#include "serviceLocator.h"
#include <SDL.h>
class entityService
{
public:
	entityService(serviceLocator* SL);
	void update();
	void draw();
	~entityService();

private:
	int detectCollision(entity* entity1, entity* entity2);
	int detectCollision(entity* ent, block* blk);
	serviceLocator* mySL;
};

