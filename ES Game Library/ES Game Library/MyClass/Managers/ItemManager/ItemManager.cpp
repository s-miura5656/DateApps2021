#include "ItemManager.h"
#include "../../Item/ItemFactory/ItemFactory.h"
#include "../../Data/WordsTable.h"

ItemManager::ItemManager()
{
	AddItemBase(SPEED_ITEM_TAG,    Vector3(0.0f, 0.5f,-5.0f));
	AddItemBase(HITPOINT_ITEM_TAG, Vector3(0.0f, 0.5f, 5.0f));
	AddItemBase(POWOR_ITEM_TAG,    Vector3(0.0f, 0.5f, 0.0f));
}

ItemManager::~ItemManager()
{
	for (auto& it = item_base.rbegin(); it != item_base.rend(); ++it)
	{
		delete (*it);
	}
}

bool ItemManager::Initialize()
{

	std::for_each(item_base.begin(), item_base.end(), [](ItemBase* itembase) { itembase->Initialize(); });

	return true;
}

int ItemManager::Update()
{
	std::for_each(item_base.begin(), item_base.end(), [](ItemBase* itembase) { itembase->Update(); });

	auto end = std::remove_if(item_base.begin(), item_base.end(), [](ItemBase* itembase) {return itembase->IsFlag() == true; });
	item_base.erase(end, item_base.end());

	return 0;
}

void ItemManager::Draw2D()
{
	std::for_each(item_base.begin(), item_base.end(), [](ItemBase* itembase) { itembase->Draw2D(); });
}

void ItemManager::Draw3D()
{
	std::for_each(item_base.begin(), item_base.end(), [](ItemBase* itembase) { itembase->Draw3D(); });
}

void ItemManager::AddItemBase(std::string name, Vector3 position)
{
	//ItemFactory* itemfactory = new ItemStationeryFactory;

	//item_base.push_back(itemfactory->Create(name, position));

	//delete itemfactory;
}