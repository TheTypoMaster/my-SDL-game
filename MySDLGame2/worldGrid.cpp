#include "worldGrid.h"
#include "grassTile.h" // for the useDefaultGrid
#include <iostream>
#include <fstream>


using namespace std;

worldGrid::worldGrid(serviceLocator* SL)
{
	mySL = SL;
	state = randomGen;
}

bool worldGrid::setServiceLocator(serviceLocator* SL)
{
	mySL = SL;
	if (mySL != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool worldGrid::placeBlock(int x, int y, int type)//if false, the player class will try to right click the block
{
	x -= mySL->globalRenderer.xOffset;
	y -= mySL->globalRenderer.yOffset;

	x /= mySL->tileWidth;
	y /= mySL->tileHeight;
	
		if (blockGrid[x][y] == NULL)//if ther isn't a block where the player wants to place one
		{
			blockGrid[x][y] = mySL->myBlockService->blocks[type];
			return true;
		}
		else
		{
			return false;
		}
	
}

bool worldGrid::breakBlock(int x, int y)
{
	x -= mySL->globalRenderer.xOffset;
	y -= mySL->globalRenderer.yOffset;

	x /= mySL->tileWidth;
	y /= mySL->tileHeight;

	//chunkX = x / chunkSize <- find the chunk

	//x -= chunkSize * (chunkX)<- find the block relative to the chunk

	if (blockGrid[x][y] != NULL)
	{
			blockGrid[x][y] = NULL;
		return true;
	}
	else
	{
		return false;
	}
}

bool worldGrid::leftClickBlock(int x, int y)
{
	x -= mySL->globalRenderer.xOffset;
	y -= mySL->globalRenderer.yOffset;

	x /= mySL->tileWidth;
	y /= mySL->tileHeight;

	return blockGrid[x][y]->onLeftClick();
}

bool worldGrid::rightClickBlock(int x, int y)
{
	x -= mySL->globalRenderer.xOffset;
	y -= mySL->globalRenderer.yOffset;

	x /= mySL->tileWidth;
	y /= mySL->tileHeight;

	return blockGrid[x][y]->onRightClick();
}


void worldGrid::draw() // if the tile/block is on the screen, draw it
{
	//i = x, j = y
	for (Uint16 i = 0; i <= gridWidth; i++)
	{
		for (Uint16 j = 0; j <= gridHeight; j++)
		{
			baseGrid[i][j]->draw(i*mySL->tileWidth, j*mySL->tileHeight);
			if (blockGrid[i][j] != NULL)
			{
				blockGrid[i][j]->draw(i * mySL->tileWidth, j * mySL->tileHeight);
			}
			
			//std::cout << "drawn " << i << " " << j << std::endl;
		}
	}
}

bool worldGrid::loadGridFromText(std::string path)
{
	ifstream baseGridFile;
	baseGridFile.open(path);
	if (!baseGridFile.is_open())
	{
		cout << "[ERROR]: File " << path << " couldn't be opened. Maby it doesn't exist." << endl;
		return false;
	}
	else
	{
	string sW, sH;
		getline(baseGridFile, sW);
		getline(baseGridFile, sH);

		if (sW == "" || sH == "")
		{
			cout << "[ERROR]: File " << path << " width or height is missing. could not load baseGrid." << endl;
			return false;
		}
		else
		{
			int w, h;
			w = atoi(sW.c_str());
			h = atoi(sH.c_str());
			return false;
			for (int i = 1; i <= w; i++)
			{
				for (int j = 1; j <= h; j++)
				{
					//insert string loading baseGrid system thing here
				}
			}
		}
	}
}

bool worldGrid::useDefaultGrid()
{
	const int width = 100;
	const int height = 100;

	state = preset;

	//instantiate the 2D vector
	//i = x, j = y
	for (int i = 0; i <= height; i++)
	{
		vector<tile* > tempTiles;
		vector<block* > tempBlocks;
		for (int j = 0; j <= width; j++)
		{
			tile* tempTile = new tile(mySL);
			//block* tempBlock = new block(mySL);
			tempTiles.push_back(tempTile);
			tempBlocks.push_back(NULL);
		}
		baseGrid.push_back(tempTiles);
		blockGrid.push_back(tempBlocks);
	}

	//setup the base grid
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			baseGrid[i][j] = new grassTile(mySL);
		}
	}

	gridWidth = width; gridHeight = height;
	return true;
}

worldGrid::~worldGrid()
{
}
