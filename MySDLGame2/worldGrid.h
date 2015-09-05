#pragma once
#include <vector>
#include "tile.h"
#include "block.h"
#include "blockService.h"
#include "chunk.h"
#include "worldGen.h"
class worldGrid
{
public:
	worldGrid(serviceLocator* SL = NULL);
	bool setServiceLocator(serviceLocator* SL);
	void draw();
	bool loadGridFromText(std::string path);
	bool useDefaultGrid();
	bool placeBlock(int x, int y, int type);
	bool placeBlockEntity(int x, int y, block* blockEntity);
	bool breakBlock(int x, int y);
	bool rightClickBlock(int x, int y);
	bool leftClickBlock(int x, int y);
	std::vector<std::vector<tile *> > baseGrid;
	std::vector<std::vector<block* > > blockGrid;
	~worldGrid();

	enum states
	{
		randomGen,
		fromFile,
		preset
	};
	states state;

	int gridWidth, gridHeight;

private:
	serviceLocator* mySL;
};

