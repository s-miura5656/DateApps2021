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

	ItemBase* item_base[2];
};