#include "ItemManager.h"
#include "../../ItemFactory/ItemFactory.h"

ItemManager::ItemManager()
{
	CItemFactory* citemfactory = new ItemStationeryFactory;

	item_base.push_back(citemfactory->Create("スピードアイテム", Vector3(0.0f,0.0f,-5.0f)));
	item_base.push_back(citemfactory->Create("体力アイテム", Vector3(0.0f, 0.0f, 5.0f)));
	item_base.push_back(citemfactory->Create("アタックアイテム", Vector3(0.0f, 0.0f, 0.0f)));

	delete citemfactory;
}

ItemManager::~ItemManager()
{
	for (auto& item : item_base)
	{
		delete item;
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
	for (auto& item : item_base)
	{
		item->Update();
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
