#include "ItemFactory.h"

ItemBase* CItemFactory::Create(std::string _type, Vector3 _position)
{
	ItemBase* itembase = CreateProduct(_type, _position);
	itembase->Initialize();
	return itembase;
}

ItemBase* ItemStationeryFactory::CreateProduct(std::string _type, Vector3 _position)
{
	if (_type == "スピードアイテム") { return new SpeedItem(_position); }

	if (_type == "アタックアイテム") { return new AttackPowerItem(_position); }

	if (_type == "体力アイテム") { return new HitPointItem(_position); }


	ASSERT(FALSE && "アイテムの名前が違う!");
}

