#include "ItemManager.h"
#include "../../Item/PoworUpItem/PoworUpItem.h"
#include "../../Item/PoworDownItem/PoworDownItem.h"
ItemManager::ItemManager()
{
	item_base[0] = new PoworUpItem;
	item_base[1] = new PoworDownItem;
}

ItemManager::~ItemManager()
{
	for (auto&& item : item_base)
	{
		delete item;
	}
}

bool ItemManager::Initialize()
{

	for (auto&& item : item_base)
	{
		item->Initialize();
	}

	return true;
}

int ItemManager::Update()
{
	for (auto&& item : item_base)
	{
		item->Update();
	}
	return 0;
}

void ItemManager::Draw2D()
{
	for (auto&& item : item_base)
	{
		item->Draw2D();
	}
}

void ItemManager::Draw3D()
{
	for (auto&& item : item_base)
	{
		item->Draw3D();
	}
}
