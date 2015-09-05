#pragma once
#include "item.h"
class itemService
{
public:
	itemService();
	item* getItem(int type);
	~itemService();

	enum itemTypes
	{
		none
	};
};

