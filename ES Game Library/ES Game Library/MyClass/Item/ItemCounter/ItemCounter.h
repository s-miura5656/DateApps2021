#pragma once

#include "../../Managers/ItemManager/ItemManager.h"

class ItemCounter
{
public:
	ItemCounter() {};
	~ItemCounter() {};

	static void SetItem(std::string tag, Vector3 pos,int point)
	{
		ItemManager::AddItemBase(tag, pos,point);
	}
private:
};