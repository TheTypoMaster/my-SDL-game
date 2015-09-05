#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "serviceLocator.h"

class tile
{
public:
	tile(serviceLocator* SL);
	virtual void update();
	virtual void draw(int x, int y);
	void setID(int ID);
	~tile();

	SDL_Rect boundingRect; // the part of the IMAGE that entities can't move over/through
	int tileID;

protected:
	serviceLocator* mySL;
	bool loadSurface(std::string path);
private:
	SDL_Surface* surface;
};