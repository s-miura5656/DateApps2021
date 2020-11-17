#pragma once

#include "../../Managers/ItemManager/ItemManager.h"

class ItemCounter
{
public:
	ItemCounter() {};
	~ItemCounter() {};

	void SetItem(std::string tag, Vector3 pos)
	{ 
		ItemManager* im = new ItemManager;
		im->AddItemBase(tag, pos);
		delete im;
	}
private:
};