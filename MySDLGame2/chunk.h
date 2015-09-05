#pragma once
#include "serviceLocator.h"
#include "tile.h"
#include "block.h"
class chunk
{
public:
	chunk(serviceLocator* SL, int x, int y);
	void draw();
	bool placeBlock(int x, int y, int type);
	bool breakBlock(int x, int y);
	~chunk();

	const int chunkSize = 10;

	block* blocks[10][10];
	tile* tiles[10][10];

	SDL_Rect chunkRect; // this isn't modified by the screen offset and must be done by classes using it
private:
	serviceLocator* mySL;
};

