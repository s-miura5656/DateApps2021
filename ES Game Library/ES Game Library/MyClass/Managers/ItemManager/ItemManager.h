#pragma once

#include "../ManagerBase.h"

class ItemBase;

class ItemManager : public ManagerBase
{
public:
	friend class ItemCounter;

	ItemManager();
	~ItemManager();


	bool Initialize() override;
	int  Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override;

private:
	static std::vector<ItemBase*> item_base;
	static void AddItemBase(std::string name, Vector3 position);

};