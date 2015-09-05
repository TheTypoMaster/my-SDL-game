#include "grassTile.h"


grassTile::grassTile(serviceLocator* SL)
	:tile(SL)
{
	loadSurface("assets/Textures/grass.png");
}

grassTile::~grassTile()
{
}
