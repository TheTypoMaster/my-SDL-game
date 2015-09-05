#include "itemService.h"


itemService::itemService()
{
}

item* itemService::getItem(int type)
{
	item* pItem = new item;


	switch (type)
	{
	case 0:
		pItem = new item;
		break;
	case 1:
		break;
	}

	return pItem;
}

itemService::~itemService()
{
}
