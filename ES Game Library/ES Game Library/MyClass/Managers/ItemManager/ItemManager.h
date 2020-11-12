#pragma once

#include "../ManagerBase.h"

class ItemBase;

class ItemManager : public ManagerBase
{
public:
	ItemManager();
	~ItemManager();

	bool Initialize();
	int  Update();
	void Draw2D();
	void Draw3D();

private:

	std::vector<ItemBase*> item_base;

	void AddItemBase(std::string name, Vector3 position);
};