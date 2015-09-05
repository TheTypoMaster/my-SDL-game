#include "inventoryService.h"


inventoryService::inventoryService()
{
}

int inventoryService::registerInventory()
{
	inventories.push_back(new inventory);
	return int(inventories.size()) - 1;
}

bool inventoryService::registerInventoryAt(int index)
{
	if (inventories[index] != NULL)
	{
		inventories[index] = new inventory;
		if (inventories[index] != NULL)
		{
			return true;
		}
	}
	return false;
}

inventory* inventoryService::getPointer(int index)
{
	return inventories[index];
}

bool inventoryService::destroyInventory(int index)
{
	if (int(inventories.size()) < index)
	{
		return false;
	}
	
	if (inventories[index] == NULL)
	{
		return false;
	}

	delete inventories[index];

	if (inventories[index] == NULL)
	{
		return true;
	}
	else
	{
		delete inventories[index];
		inventories[index] = NULL;
		return true;
	}
}

inventoryService::~inventoryService()
{
}
