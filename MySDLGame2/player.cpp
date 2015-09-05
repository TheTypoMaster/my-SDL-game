#include "player.h"


player::player(serviceLocator* SL)
	:mySL(SL)
{
	//setup player dimensions for collision detection
	playerRect.w = 20;
	playerRect.h = 40;

	playerRect.x = (mySL->globalRenderer.screenWidth / 2) - (playerRect.w / 2);
	playerRect.y = (mySL->globalRenderer.screenHeight / 2) - (playerRect.h / 2);

	playerInvIndex = mySL->myInventoryService->registerInventory();
	playerInv = mySL->myInventoryService->getPointer(playerInvIndex);

	viewport = { 18, 652, 29, 51 };
}

void player::draw()
{
	mySL->globalRenderer.drawViewportSurface(mySL->myImageService.surfaces[mySL->myImageService.saraSheet], viewport, playerRect);

	animate();
}

void player::animate()
{
	animateCounter++;

	if (animateCounter == animateCounterStart)
	{
		viewport.x += 64;
		if (viewport.x == 530)
		{
			viewport.x = 18;
		}
		animateCounter = 0;
	}
}

void player::update()
{
	move();

	mySL->globalRenderer.xOffset -= xVel;
	mySL->globalRenderer.yOffset -= yVel;

	if (mySL->globalRenderer.xOffset > 0)
	{
		mySL->globalRenderer.xOffset = 0;
	}

	if (mySL->globalRenderer.yOffset > 0)
	{
		mySL->globalRenderer.yOffset = 0;
	}

	if (placeTimer > 0)
		placeTimer -= 1;
	//if the right mouse button is down, place a block
	if (SDL_GetMouseState(&mPos.x, &mPos.y) & SDL_BUTTON_RMASK && placeTimer == 0)
	{
		mySL->myWorldService->worlds[mySL->myWorldService->currentWorld].mainWorld.placeBlock(mPos.x, mPos.y, 1);
		placeTimer = placeTimerStart;
	}
	//if the left mouse button is down, break the block
	if (SDL_GetMouseState(&mPos.x, &mPos.y) & SDL_BUTTON_LMASK)
	{
		mySL->myWorldService->worlds[mySL->myWorldService->currentWorld].mainWorld.breakBlock(mPos.x, mPos.y);
	}
}

void player::eventUpdate(SDL_Event nextEvent)
{
	if (nextEvent.type == SDL_MOUSEWHEEL)
	{
		selectedItem += nextEvent.wheel.y;
		if (selectedItem >= 9)
		{
			selectedItem = 0;
		}
	}
}

void player::tickBreak()
{

}

void player::placeBlock()
{

}

void player::move()
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	//up
	if (currentKeyStates[SDL_SCANCODE_W])
	{
		yVel = speed * -1;
	}

	//down
	if (currentKeyStates[SDL_SCANCODE_S])
	{
		yVel = speed;
	}

	//up and down
	if (currentKeyStates[SDL_SCANCODE_W] && currentKeyStates[SDL_SCANCODE_S])
	{
		yVel = 0;
	}

	//no vertical movement
	if (!currentKeyStates[SDL_SCANCODE_W] && !currentKeyStates[SDL_SCANCODE_S])
	{
		yVel = 0;
	}


	//left
	if (currentKeyStates[SDL_SCANCODE_A])
	{
		xVel = speed * -1;
	}

	//right
	if (currentKeyStates[SDL_SCANCODE_D])
	{
		xVel = speed;
	}

	//left and right
	if (currentKeyStates[SDL_SCANCODE_A] && currentKeyStates[SDL_SCANCODE_D])
	{
		xVel = 0;
	}

	//no horisontal movement
	if (!currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D])
	{
		xVel = 0;
	}
}

inventory* player::getInvPointer()
{
	return playerInv;
}

player::~player()
{
}
