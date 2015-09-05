#pragma once
#include "inventory.h"
#include <vector>

class inventoryService
{
public:
	inventoryService();
	int registerInventory();
	bool registerInventoryAt(int index);
	inventory* getPointer(int index);
	bool destroyInventory(int index);
	~inventoryService();

	std::vector<inventory* > inventories;
};

