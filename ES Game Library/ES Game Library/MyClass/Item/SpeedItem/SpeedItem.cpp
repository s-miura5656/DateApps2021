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
	_map_data = new IMapData;
}

SpeedItem::~SpeedItem()
{
	delete _map_data;
	delete _i_player_data;
	_hit_box.reset();
}

bool SpeedItem::Initialize()
{
	_speed = 0.09f;

	auto data = _map_data->GetData();

	int x = fabsf(_position.x);
	int z = fabsf(_position.z);

	data[z][x] = 'a';
	_map_data->SetData(data);

	_model = ResouceManager::Instance().LoadModelFile(_T("Item/player_speedup_item.X"));
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	material.Ambient = Color(1.0f, 1.0f, 1.0f);

	//BoxShape(5);

	_model->SetMaterial(material);

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
			_i_player_data->SetParameter_PowerUp(name, true);
			_i_player_data->SetSpeed(name, _speed);
			Removeflag = true;
			auto data = _map_data->GetData();

			int x = fabsf(_position.x);
			int z = fabsf(_position.z);

			data[z][x] = ' ';
			_map_data->SetData(data);
		}
	}

	return 0;
}
