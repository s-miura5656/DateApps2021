#include "HitPointItem.h"
#include "../../Data/GameData.h"

HitPointItem::HitPointItem(Vector3 position, std::string name)
{
	this->_position = position;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(name);
	_iplayer_data = new IPrayerData;
}

HitPointItem::~HitPointItem()
{
	delete _iplayer_data;
}


bool HitPointItem::Initialize()
{
	_hit_point = 1000.f;

	Material material;
	material.Diffuse = Color(0.0f, 1.0f, 0.0f);
	material.Ambient = Color(0.0f, 0.75f, 0.0f);

	SphereShape();

	_box->SetMaterial(material);
	
	return true;
}

int HitPointItem::Update()
{
	RotationItem();

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
