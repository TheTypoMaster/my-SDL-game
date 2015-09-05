#pragma once
// this class will be used by the worldGrid class to generate new chunks
//it will return the generated chunks from the x and y coordinated passed into it
#include "serviceLocator.h"
#include "chunk.h"
class worldGen
{
public:
	worldGen(serviceLocator* SL, int seed);
	chunk generateChunk(int x, int y);
	~worldGen();
private:
	serviceLocator* mySL;
	int genSeed;
};