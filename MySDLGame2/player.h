#pragma once
#include <SDL.h>
#include "worldService.h"
#include "inventory.h"
#include "inventoryDisplay.h"
#include "serviceLocator.h"
#include "entity.h"
class player : public entity
{
	friend playerService;
public:
	player(serviceLocator* SL);
	void update();
	void eventUpdate(SDL_Event nextEvent);
	void draw();
	~player();

	int playerInvIndex;
private:
	void move();
	void updtaeKeys();
	void animate();
	void tickBreak();
	void placeBlock();
	inventory* getInvPointer();

	inventory* playerInv;
	int selectedItem;

	SDL_Point mPos;
	SDL_Rect playerRect;
	SDL_Rect viewport;
	int xVel, yVel;
	const int speed = 1;

	const int placeTimerStart = 10;
	int placeTimer = 0;

	serviceLocator* mySL;

	int animateCounter;
	const int animateCounterStart = 6;

	int breakCounter;
	int breakCounterEnd;//will be set determining on the block's base break speed and the tool's correct usage break speed/incorrect usage break speed
};

