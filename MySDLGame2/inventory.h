#pragma once
#include "item.h"
#include <vector>

class inventory
{
public:
	inventory();
	~inventory();


	struct stack
	{
		int amount;
		item Item;
		int maxStack;
	};

	std::vector<stack> itemStack;

	int maxSize;
};

