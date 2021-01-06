#include "PointItem.h"
#include "../../Data/WordsTable.h"

PointItem::PointItem(Vector3 position, std::string name, int point)
{
	this->_position = position;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(name);
	_hit_box->SetHitBox(1, 1, 1);
	_point = point;
	_i_player_data = new IPrayerData;
}

PointItem::~PointItem()
{
	delete _i_player_data;
	_hit_box.reset();
}

bool PointItem::Initialize()
{
	_speed = 0.01f;

	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	material.Ambient = Color(0.0f, 0.0f, 0.75f);
	if (_point >= 300)
	{
		material.Ambient = Color(1.0f, 1.0f, 1.0f);
	}

	BoxShape(_point / 100);

	_box->SetMaterial(material);

	return true;
}

int PointItem::Update()
{
	RotationItem();

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		if (_i_player_data->GetState(name) != PlayerEnum::Animation::WAIT && _i_player_data->GetState(name) != PlayerEnum::Animation::MOVE)
		{
			continue;
		}
		if (_hit_box->IsHitObjectsSquare(name))
		{
			_i_player_data->SetRankingPoint(name, _i_player_data->GetRankingPoint(name) + _point);
			ItemEffect(name);
			Removeflag = true;
		}
	}

	return 0;
}
