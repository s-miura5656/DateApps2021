#include "AttackPowerItem.h"
#include "../../Data/WordsTable.h"


AttackPowerItem::AttackPowerItem(Vector3 position, std::string name)
{
	this->_position = position;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(name);
	_hit_box->SetHitBox(1, 1, 1);
	_iplayer_data = new IPrayerData;
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

	BoxShape();

	_box->SetMaterial(material);

	return true;
}

int AttackPowerItem::Update()
{
	RotationItem();

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		if (_hit_box->IsHitObjects(name))
		{
			/*auto&& hit_box = _hit_box->GetHitBoxTag(name);
			MODEL hit_model = hit_box->GetModelTag();

			hit_model->IntersectRay(_hit_box->GetModelTag()->GetPosition(), hit_model->GetPosition(), &hit_box->_dist);*/

			ItemEffect(name);
			//Removeflag = true;
		}
		else
		{
			/*auto&& hit_box = _hit_box->GetHitBoxTag(name);
			hit_box->_dist = FLT_MAX;*/
		}
	}

	return 0;
}

