#include "SpeedItem.h"
#include "../../Data/WordsTable.h"

SpeedItem::SpeedItem(Vector3 position, std::string name)
{
	this->_position = position;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(name);
	_hit_box->SetHitBox(1, 1, 1);
	_i_player_data = new IPrayerData;
}

SpeedItem::~SpeedItem()
{
	delete _i_player_data;
	_hit_box.reset();
}

bool SpeedItem::Initialize()
{
	_speed = 0.09f;

	Material material;
	material.Diffuse = Color(0.0f, 0.0f, 1.0f);
	material.Ambient = Color(0.0f, 0.0f, 0.75f);

	BoxShape(5);

	_box->SetMaterial(material);

	return true;
}

int SpeedItem::Update()
{
	RotationItem();

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		if (_hit_box->IsHitObjectsSquare(name))
		{
			//ItemEffect(name);
			_i_player_data->SetParameter_Change_Flag(name, true);
			_i_player_data->SetSpeed(name, _speed);
			Removeflag = true;
		}
	}

	return 0;
}
