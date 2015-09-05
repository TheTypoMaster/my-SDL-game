#pragma once
#include <SDL.h>
#include "serviceLocator.h"
#include "inventoryService.h"
#include "inventory.h"
class inventoryDisplay
{
public:
	inventoryDisplay();
	void update();
	void draw();
	~inventoryDisplay();
};

