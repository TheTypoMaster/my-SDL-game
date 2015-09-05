#include "block.h"
#include "blockService.h"

block::block(serviceLocator* SL)
	:mySL(SL)
{
}

void block::draw(int x, int y)
{
	drawRect.x = x + mySL->globalRenderer.xOffset;
	drawRect.y = y + mySL->globalRenderer.yOffset;

	mySL->globalRenderer.drawSurface(surface, drawRect);
}

void block::update()
{

}

bool block::onLeftClick() //returns false if the operation couldn't be completed
{
	return true;
}

bool block::onRightClick() //returns false if the operation couldn't be completed
{
	return true;
}

bool block::onCollision() // returns true if the block is solid
{
	return false;
}

bool block::onMouseHover()
{
	return true;
}

bool block::onPlace() //returns false if the block shouldn't be placed (the block is placed, does a check and then determines whether it can stay)
{
	return true;
}

bool block::onBreak() //returns true to break the block
{
	return true;
}

bool block::loadSurface(std::string path)
{
	surface = mySL->myImageService.loadImageReturn(path);
	return true;
}

void block::setID(int ID)
{
	blockID = ID;
}

block::~block()
{
}
