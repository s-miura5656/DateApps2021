#include "ItemFactory.h"
#include "../../Data/WordsTable.h"

ItemBase* ItemFactory::Create(std::string tag, Vector3 position)
{
	ItemBase* itembase = CreateProduct(tag, position);
	itembase->Initialize();
	return itembase;
}

ItemBase* ItemStationeryFactory::CreateProduct(std::string tag, Vector3 position)
{
	if (tag == SPEED_ITEM_TAG) { return new SpeedItem(position, tag); }

	if (tag == POWOR_ITEM_TAG) { return new AttackPowerItem(position, tag); }

	if (tag == HITPOINT_ITEM_TAG) { return new HitPointItem(position, tag); }


	ASSERT(FALSE && "アイテムの名前が違う!");
}

