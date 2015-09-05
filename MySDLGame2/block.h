#pragma once
#include <SDL.h>
#include "serviceLocator.h"
class block
{
public:
	block(serviceLocator* SL);
	virtual void update();
	virtual void draw(int x, int y);
	void setID(int ID);
	~block();

	virtual bool onLeftClick();
	virtual bool onRightClick();
	virtual bool onCollision();
	virtual bool onMouseHover();
	virtual bool onBreak();
	virtual bool onPlace();

	SDL_Rect tileRect;
	SDL_Rect drawRect;
	bool solid;
	int blockID;

	struct material
	{
		serviceLocator::materialTypes type;
		serviceLocator::toolTypes effectiveTool;
		int harvestLevel;
		int baseHarvestTime;
	};

protected:
	serviceLocator* mySL;
	bool loadSurface(std::string path);
	material blockMaterial;
private:
	SDL_Surface* surface;
	bool randomUpdates;
};

