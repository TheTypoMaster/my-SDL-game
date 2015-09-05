#pragma once
#include "item.h"
#include <vector>
class itemStack
{
public:
	itemStack();
	bool setItemType(int type);
	~itemStack();

	std::vector<item> items;
	int maxStack;
};

