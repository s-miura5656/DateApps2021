#include "ItemManager.h"
#include "../../Factorys/ItemFactory/ItemFactory.h"
#include "../../Data/GameData.h"

ItemManager::ItemManager()
{
	ItemFactory* itemfactory = new ItemStationeryFactory;

	item_base.push_back(itemfactory->Create(SPEED_ITEM_TAG, Vector3(0.0f,0.0f,-5.0f)));
	item_base.push_back(itemfactory->Create(HITPOINT_ITEM_TAG, Vector3(0.0f, 0.0f, 5.0f)));
	item_base.push_back(itemfactory->Create(POWOR_ITEM_TAG, Vector3(0.0f, 0.0f, 0.0f)));

	delete itemfactory;
}

ItemManager::~ItemManager()
{
	for (int i = item_base.size() - 1; i >= 0; --i)
	{
		delete item_base[i];
	}
}

bool ItemManager::Initialize()
{

	for (auto& item : item_base)
	{
		item->Initialize();
	}

	return true;
}

int ItemManager::Update()
{
	auto item = item_base;

	for (int i = 0; i < item.size(); ++i)
	{
		if (item[i]->Update() == END) 
			item_base.erase(item_base.begin() + i);
	}

	return 0;
}

void ItemManager::Draw2D()
{
	for (auto& item : item_base)
	{
		item->Draw2D();
	}
}

void ItemManager::Draw3D()
{
	for (auto& item : item_base)
	{
		item->Draw3D();
	}
}
