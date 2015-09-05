#include "testBlock.h"


testBlock::testBlock(serviceLocator* SL)
	:block(SL)
{
	loadSurface("assets/Textures/test block.png");
}

testBlock::~testBlock()
{
}
