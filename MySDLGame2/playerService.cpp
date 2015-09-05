#include "playerService.h"


playerService::playerService()
{
}

bool playerService::init()
{
	playerInventory = myPlayer->getInvPointer();
	if (playerInventory == NULL)
		return false;
	playerRect = myPlayer->playerRect;
	if (playerRect.x == 0 || playerRect.y == 0 || playerRect.w == 0 || playerRect.h == 0)
		return false;

	return true;
}

playerService::~playerService()
{
}
