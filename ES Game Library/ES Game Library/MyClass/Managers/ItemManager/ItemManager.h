#pragma once

#include "../ManagerBase.h"

class ItemBase;

class ItemManager : public ManagerBase
{
public:
	friend class ItemCounter;

	ItemManager();
	~ItemManager();


	bool Initialize();
	int  Update();
	void Draw2D();
	void Draw3D();

private:
	static std::vector<ItemBase*> item_base;
	static void AddItemBase(std::string name, Vector3 position);

};