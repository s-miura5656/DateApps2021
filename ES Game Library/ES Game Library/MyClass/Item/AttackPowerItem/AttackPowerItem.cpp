#include "AttackPowerItem.h"
#include "../../Data/GameData.h"

AttackPowerItem::AttackPowerItem(Vector3 position, std::string name)
{
	this->_position = position;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(name);
	_hit_box->SetHitBox(1, 1, 1);
	_iplayer_data = new IPrayerData;

	_rotation = 0.0f;
}

AttackPowerItem::~AttackPowerItem()
{
	delete _iplayer_data;
}

bool AttackPowerItem::Initialize()
{
	_attack_powor = 100;
	
	Material material;
	material.Diffuse = Color(1.0f, 0.0f, 0.0f);
	material.Ambient = Color(0.75f, 0.0f, 0.0f);

	SphereShape();

	_box->SetMaterial(material);

	return true;
}

int AttackPowerItem::Update()
{

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		if (_hit_box->IsHitObjects(name))
		{
			ItemEffect(name);
			Removeflag = true;
		}
	}

	return 0;
}

