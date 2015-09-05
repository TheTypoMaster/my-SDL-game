#include "chunk.h"
#include "blockService.h"


chunk::chunk(serviceLocator* SL, int x, int y)
	:mySL(SL)
{
	chunkRect.x = x * chunkSize;
	chunkRect.y = y * chunkSize;
	chunkRect.w = chunkSize;
	chunkRect.h = chunkSize;
}

void chunk::draw()
{
	//i = x, j = y
	for (Uint16 i = 0; i <= chunkSize; i++)
	{
		for (Uint16 j = 0; j <= chunkSize; j++)
		{
			tiles[i][j]->draw(i*mySL->tileWidth, j*mySL->tileHeight);
			if (blocks[i][j] != NULL)
			{
				blocks[i][j]->draw(i * mySL->tileWidth, j * mySL->tileHeight);
			}

			//std::cout << "drawn " << i << " " << j << std::endl;
		}
	}
}

bool chunk::placeBlock(int x, int y, int type)
{
	if (blocks[x][y] == NULL)//if there isn't a block where the player wants to place one
	{
		blocks[x][y] = mySL->myBlockService->blocks[type];
		return true;
	}
	else
	{
		return false;
	}
}

bool chunk::breakBlock(int x, int y)
{
	if (blocks[x][y] != NULL)
	{
		blocks[x][y] = NULL;
		return true;
	}
	else
	{
		return false;
	}
}

chunk::~chunk()
{
}
