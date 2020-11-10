#include "ItemManager.h"


ItemManager::ItemManager()
{
	item_base[0] = new SpeedItem;
	item_base[1] = new AttackPowerItem;
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
