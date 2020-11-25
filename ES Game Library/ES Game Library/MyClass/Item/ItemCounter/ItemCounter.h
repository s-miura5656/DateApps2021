#pragma once

#include "../../Managers/ItemManager/ItemManager.h"

class ItemCounter
{
public:
	ItemCounter() {};
	~ItemCounter() {};

	void SetItem(std::string tag, Vector3 pos)
	{
		ItemManager::AddItemBase(tag, pos);
	}
private:
};