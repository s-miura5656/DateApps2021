#include "ItemFactory.h"

ItemBase* CItemFactory::Create(std::string _type, Vector3 _position)
{
	ItemBase* itembase = CreateProduct(_type, _position);
	itembase->Initialize();
	return itembase;
}

ItemBase* ItemStationeryFactory::CreateProduct(std::string _type, Vector3 _position)
{
	if (_type == "�X�s�[�h�A�C�e��") { return new SpeedItem(_position); }

	if (_type == "�A�^�b�N�A�C�e��") { return new AttackPowerItem(_position); }

	if (_type == "�̗̓A�C�e��") { return new HitPointItem(_position); }


	ASSERT(FALSE && "�A�C�e���̖��O���Ⴄ!");
}

