#pragma once
#include "serviceLocator.h"
#include <vector>
#include "block.h"
class blockService
{
public:
	blockService(serviceLocator* SL);
	void update();
	int registerBlock(block* newBlock);
	bool registerForUpdates(block* newBlock); //for animated textures
	~blockService();

	std::vector<block* > blocks;

	enum blockType// <- for testing purposes. to be removed after inventory is fully implemented
	{
		none,
		test,
		wood,
		stone,
		workbench
	};

private:
	std::vector<block* > updates;
	//int updatesSize
	//int blocksSize;
	serviceLocator* mySL;
};

