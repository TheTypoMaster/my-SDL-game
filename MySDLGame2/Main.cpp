#pragma region TODO and notes
//TODO
//* = don't have to complete


//for lighting, incorperate openGL*
//setup renderer functions for the Texture type*

//setup GUI for inventory - an inventory menu?
//	use ui_big_pieces_0.png for the inventory
//setup menus*
//setup menu elements*
//use function pointers with buttons for callback*
//test out the GUI API
//move the loading of GUI images to the UI class
//	have different arrays for each colour of UI
//	have one enum for all of the above arrays
//	have a seperate array for general UI stuff

//use scripting to create AI packages
//use lua scripts to create items?

//complete the terrain generation class
//research how to randomly generate terrain :P

//incorperate chunks into worldGrid

//the entity controller will register each entity to one or more chunks (if it is across a chunk boundary)
//the controller will deal with collisions with other entities and blocks using a vector of structs
	//the structs will have an entity pointer and 4 chunk pointers
//the controller will handle pushing of other entities and damaging
	//when a mob comes into collision with another mob, it calls a function of the colliding entity with a pointer to the other entity (for damaging etc.)

//make new functions for the entity class
//void onCollide(entity* collider)
//void onCollide(block* collider)
//bool damage(int amount)
//bool push(int xVel, int yVel)
#pragma endregion

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_net.h>
#include <SDL_mixer.h>
#include <lua.hpp>
#include "worldService.h"
#include "playerService.h"
#include "UI.h"
#include "serviceLocator.h"
#include "world.h"
#include "counter.h"
#include "testBlock.h"
#include "block.h"
#include "toolTip.h"

#pragma region defenitions
bool initAll();
bool initServices();
void mainGame();
bool loadAllTextures();
bool loadAllFonts();
bool loadAllSounds();
bool loadUI();
bool initSL();
bool initPlayer();
bool initBlocks();

void eventUpdate();
void update();
void draw();
#pragma endregion

button* startGame;

const int FPS = 60;
const int screenTicksPerFrame = 1000 / FPS;

enum class gameStates
{
	splash,
	play,
	paused,
	over,
	end
};

gameStates myGameState;

serviceLocator* mySL;

using namespace std;

int main(int argc, char* argv[])
{
	mySL = new serviceLocator; //instantiate the service locator
	if (initAll())
	{
		myGameState = gameStates::splash;
		mySL->myWorldService->getNewWorld(mySL);
		mySL->myWorldService->worlds[0].getNewWorldGrid();
		mySL->myWorldService->worlds[0].mainWorld.useDefaultGrid();

		initPlayer();

		startGame = mySL->myUI->registerButton();
		startGame->setPos(mySL->globalRenderer.screenWidth / 2 - 100, mySL->globalRenderer.screenHeight / 2 - 25);
		startGame->setSize(200, 50);
		startGame->setText("Start Game!");
		startGame->setType(button::type1);

		mainGame();
	}
	else
	{
		SDL_Delay(20000); // 20 seconds
	}
	SDL_Quit();

	return 0;
}

void mainGame()
{
	SDL_Rect rectangle;
	SDL_Surface* surface = mySL->myImageService.surfaces[0];
	rectangle.x = 0; rectangle.y = 0; rectangle.w = 100; rectangle.h = 100;
	bool quit = false;
	cout << "[INFO]: Entering the game loop" << endl;

	counter capTimer;

	counter fpsTimer;
	fpsTimer.start();
	int countedFrames = 0;

	while (!quit && myGameState != gameStates::end)
	{

		capTimer.start();
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			{
				myGameState = gameStates::end;
			}

			mySL->currentEvent = e;
			eventUpdate();
		}

		//Calculate and correct fps
		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			//avgFPS = 0;
		}

		//output the agerage fps to the console
		//cout << (int)avgFPS << endl;

		//update then draw the game
		update();
		draw();

		//"frame capping"
		int frameTicks = capTimer.getTicks();
		if (frameTicks < screenTicksPerFrame)
		{
			SDL_Delay(screenTicksPerFrame - frameTicks);
		}

		++countedFrames;
	}
}

void eventUpdate()
{
	switch (myGameState)
	{
	case gameStates::play:
		break;
	case gameStates::splash:
		break;
	case gameStates::end:
		break;
	case gameStates::over:
		break;
	case gameStates::paused:
		break;
	}

	mySL->myPlayerService->myPlayer->eventUpdate(mySL->currentEvent);
	mySL->myUI->eventUpdate();
}

void update()
{
	switch (myGameState)
	{
	case gameStates::play:
		mySL->myPlayerService->myPlayer->update();
		break;
	case gameStates::splash:
		if (startGame->getState())
		{
			myGameState = gameStates::play;
			startGame->disable();
		}
		break;
	case gameStates::end:
		break;
	case gameStates::over:
		break;
	case gameStates::paused:
		break;
	}

	mySL->myUI->update();
}

void draw()
{

	switch (myGameState)
	{
	case gameStates::play:
		mySL->myWorldService->worlds[0].drawCurrentGrid();
		mySL->myPlayerService->myPlayer->draw();
		break;
	case gameStates::splash:
		break;
	case gameStates::end:
		break;
	case gameStates::over:
		break;
	case gameStates::paused:
		mySL->myWorldService->worlds[0].drawCurrentGrid();
		mySL->myPlayerService->myPlayer->draw();
		break;
	}
	mySL->myUI->draw();

	mySL->globalRenderer.drawScreen(); //no touchey
}

bool initSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "[ERROR]: SDL failed to init. SDL_image Error: " << IMG_GetError() << endl;
		return false;
	}
	else
	{
		cout << "[INFO]: SDL initalised." << endl;
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			cout << "[ERROR]: IMG didn't initialise properly. SDL Error " << SDL_GetError() << endl;
			return false;
		}
		else
		{
			cout << "[INFO]: IMG initialised." << endl;
			//Initialize SDL_ttf
			if (TTF_Init() == -1)
			{
				cout << "[ERROR]: SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
				return false;
			}
			else
			{
				return true;
			}
		}

	}
}

bool initAll()
{
	if (initSDL())
	{
		if (mySL != NULL)
		{
			if (mySL->globalRenderer.init())
			{
				cout << "[INFO]: initialised successfully" << endl;
				cout << "[INFO]: initialising service locator" << endl;
				if (!initSL())
				{
					cout << "[ERROR]: the service locator wasn't initialised correctly" << endl;
					return false;
				}
				else
				{
					cout << "[IFNO]: loading images" << endl;
					if (!loadAllTextures())
					{
						cout << "[ERROR]: The images weren't loaded" << endl;
						return false;
					}
					else
					{
						cout << "[INFO]: the images were loaded" << endl;
						if (!loadAllFonts())
						{
							cout << "[ERROR]: the fonts wern't loaded" << endl;
							return false;
						}
						else
						{
							cout << "[INFO]: the fonts were loaded" << endl;
							if (!loadAllSounds())
							{
								cout << "[ERROR]: the sounts weren't loaded correctly" << endl;
								return false;
							}
							else
							{
								cout << "[INFO]: the sounds were loaded" << endl;
								if (!initBlocks())
								{
									cout << "[ERROR]: the blocks weren't initialised correctly" << endl;
									return false;
								}
								else
								{
									return true;
								}
							}
						}
					}
				}
			}
			else
			{
				cout << "[ERROR]: globalRenderer couldn't be initialised" << endl;
				return false;
			}
		}
		else
		{
			cout << "[ERROR]: The service locator is NULL" << endl;
			return false;
		}
	}
	else
	{
		cout << "[ERROR]: SDL wasn't initialised" << endl;
		return false;
	}
}

bool loadAllTextures()
{
	bool loaded = true;
	//missing texture texture
	if (!mySL->myImageService.loadImage("assets/Textures/missing texture.png"))
	{
		loaded = false;
		cout << "[ERROR]: failed to load 'assets/Textures/missing texture.png'" << endl;
	}
	//the sara sprite sheet
	if (!mySL->myImageService.loadImage("assets/Textures/SaraFullSheet.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load 'assets/Textures/SaraFullSheet.png'" << endl;
	}
	//the seperate UI sections
	if (!loadUI())
	{
		loaded = false;
		cout << "[ERROR]: UI failed to load" << endl;
	}
	return loaded;
}

bool loadBlueUI()
{
	bool loaded = true;

	const string path = "assets/Textures/UI/Seperate/blue_";

	//check mark box
	if (!mySL->myImageService.loadImage(path + "boxCheckMark.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_boxCheckMark.png\"" << endl;
	}
	//cross box
	if (!mySL->myImageService.loadImage(path + "boxCross.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_boxCross.png\"" << endl;
	}
	//radio button
	if (!mySL->myImageService.loadImage(path + "boxTick.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_boxTick.png\"" << endl;
	}
	//button type 1 up
	if (!mySL->myImageService.loadImage(path + "button00.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button00.png\"" << endl;
	}
	//button type 1 down
	if (!mySL->myImageService.loadImage(path + "button01.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button01.png\"" << endl;
	}
	//button type 2 up
	if (!mySL->myImageService.loadImage(path + "button02.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button02.png\"" << endl;
	}
	//button type 2 down
	if (!mySL->myImageService.loadImage(path + "button03.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button03.png\"" << endl;
	}
	//button type 3 up
	if (!mySL->myImageService.loadImage(path + "button04.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button04.png\"" << endl;
	}
	//button type 3 down
	if (!mySL->myImageService.loadImage(path + "button05.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button05.png\"" << endl;
	}
	//button type 4 up
	if (!mySL->myImageService.loadImage(path + "button07.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button07.png\"" << endl;
	}
	//button type 4 down
	if (!mySL->myImageService.loadImage(path + "button08.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button08.png\"" << endl;
	}
	//button type 5 up
	if (!mySL->myImageService.loadImage(path + "button09.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button09.png\"" << endl;
	}
	//button type 5 down
	if (!mySL->myImageService.loadImage(path + "button10.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button 10.png\"" << endl;
	}
	//button type 6 up
	if (!mySL->myImageService.loadImage(path + "button11.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button11.png\"" << endl;
	}
	//button type 6 down
	if (!mySL->myImageService.loadImage(path + "button12.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_button12.png\"" << endl;
	}
	//blue check mark
	if (!mySL->myImageService.loadImage(path + "checkmark.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_checkmark.png\"" << endl;
	}
	//blue circle
	if (!mySL->myImageService.loadImage(path + "circle.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_circle.png\"" << endl;
	}
	//blue cross
	if (!mySL->myImageService.loadImage(path + "cross.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_cross.png\"" << endl;
	}
	//blue panel
	if (!mySL->myImageService.loadImage(path + "panel.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_panel.png\"" << endl;
	}
	//blue slider down
	if (!mySL->myImageService.loadImage(path + "sliderDown.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_sliderDown.png\"" << endl;
	}
	//blue slider left
	if (!mySL->myImageService.loadImage(path + "sliderLeft.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_sliderLeft.png\"" << endl;
	}
	//blue slider right
	if (!mySL->myImageService.loadImage(path + "sliderRight.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_sliderRight.png\"" << endl;
	}
	//blue slider up
	if (!mySL->myImageService.loadImage(path + "sliderUp.png"))
	{
		loaded = false;
		cout << "[ERROR]: Failed to load \"blue_sliderUp.png\"" << endl;
	}
	//blue tick (circle mark for radio buttons)
	return loaded;
}

bool loadGreenUI()
{
	bool loaded = true;

	return loaded;
}

bool loadRedUI()
{
	bool loaded = true;

	return loaded;
}

bool loadGreyUI()
{
	bool loaded = true;

	return loaded;
}

bool loadYellowUI()
{
	bool loaded = true;

	return loaded;
}

bool loadUI()
{
	bool loaded = true;

	const string path = "assets/Textures/UI/Seperate/";

	if (!loadBlueUI())
		loaded = false;

	if (!loadGreenUI())
		loaded = false;

	if (!loadGreyUI())
		loaded = false;

	if (!loadRedUI())
		loaded = false;

	if (!loadYellowUI())
		loaded = false;

	if (!mySL->myImageService.loadImage(path + "grey_sliderEnd.png"))
	{
		cout << "[ERROR]: Failed to load \"grey_sliderEnd.png\"" << endl;
		loaded = false;
	}

	if (!mySL->myImageService.loadImage(path + "grey_sliderHorizontal.png"))
	{
		cout << "[ERROR]: Failed to load \"grey_sliderVertical.png\"" << endl;
		loaded = false;
	}

	if (!mySL->myImageService.loadImage(path + "grey_sliderVertical.png"))
	{
		cout << "[ERROR]: Failed to load \"grey_sliderVertical.png\"" << endl;
		loaded = false;
	}
	
	return loaded;
}

bool loadAllFonts()
{
	bool loaded = true;
	string path = "assets/Fonts/";

	//UI font (the font that came with the UI pack)
	if (!mySL->myImageService.loadFont(path + "kenvector_future.ttf", 15))
	{
		cout << "[ERROR]: failed to load font " << path + "kenvector_future.ttf" << endl;
		loaded = false;
	}
	//UI font thin
	if (!mySL->myImageService.loadFont(path + "kenvector_future_thin.ttf", 10))
	{
		cout << "[ERROR]: failed to load font " << path + "kenvector_future_thin.ttf" << endl;
		loaded = false;
	}

	return loaded;
}

bool loadAllSounds()
{
	bool loaded = true;

	return loaded;
}

bool initSL()
{
	worldService* temp;
	temp = new worldService;
	mySL->myWorldService = temp;
	if (mySL->myWorldService == NULL)
	{
		cout << "[ERROR]: world service wasn't initialised correctly" << endl;
		return false;
	}

	mySL->myImageService.globalRenderer = &mySL->globalRenderer;
	if (mySL->myImageService.globalRenderer == NULL)
	{
		cout << "[ERROR]: image service wasn't initialised correctly" << endl;
		return false;
	}

	playerService* PS = new playerService;
	mySL->myPlayerService = PS;
	if (mySL->myPlayerService == NULL)
	{
		cout << "[ERROR]: player service wasn't initialised correctly" << endl;
		return false;
	}

	blockService* BS = new blockService(mySL);
	mySL->myBlockService = BS;
	if (mySL->myBlockService == NULL)
	{
		cout << "[ERROR]: block service wasn't initialised correctly" << endl;
		return false;
	}

	inventoryService* IS = new inventoryService;
	mySL->myInventoryService = IS;
	if (mySL->myInventoryService == NULL)
	{
		cout << "[ERROR]: Inventory service wasn't initialised correctly" << endl;
		return false;
	}

	UI* UIt = new UI(mySL);
	mySL->myUI = UIt;
	if (mySL->myUI == NULL)
	{
		cout << "[ERROR]: UI couldn't be initialised correctly" << endl;
		return false;
	}

	return true;
}

bool initPlayer()
{
	mySL->myPlayerService->myPlayer = new player(mySL);
	if (mySL->myPlayerService->myPlayer == NULL)
	{
		cout << "[ERROR]: The player service couldn't be initialised" << endl;
		return false;
	}

	if (!mySL->myPlayerService->init())
	{
		cout << "[ERROR]: the player service couldn't be initialised" << endl;
		return false;
	}
	return true;
}

bool initBlocks()
{
	mySL->myBlockService->registerBlock(new block(mySL));
	mySL->myBlockService->registerBlock(new testBlock(mySL));
	return true;
}