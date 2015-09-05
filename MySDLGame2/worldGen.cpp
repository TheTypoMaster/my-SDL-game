#include "worldGen.h"


worldGen::worldGen(serviceLocator* SL, int seed)
	:mySL(SL),
	genSeed(seed)
{
}

chunk worldGen::generateChunk(int x, int y)
{
	chunk newChunk(mySL, x, y);
	return newChunk;
}

worldGen::~worldGen()
{
}
