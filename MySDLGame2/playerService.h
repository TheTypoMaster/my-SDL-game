#pragma once
#include "player.h"
#include "entity.h"
#include "block.h"
class playerService
{
public:
	playerService();
	//bool spawnPlayerAt(int x, int y);
	//bool damagePlayer(entity* attacker);
	//bool hazardDamagePlayer(block* source);
	SDL_Rect getPlayerRect();
	bool addItemToInv();
	bool removeItemFromInv();
	bool init();
	~playerService();

	player* myPlayer;
private:
	inventory* playerInventory;
	SDL_Rect playerRect;
};

