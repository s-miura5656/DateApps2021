#include "SpeedItem.h"
#include "../../Data/WordsTable.h"
#include "../../Players/PlayerBase.h"
#include "../../Scenes/Main/Camera/MainCamera.h"
#include "../../Managers/AudioManager/AudioManager.h"
SpeedItem::SpeedItem(Vector3 position, std::string name)
{
	this->_position = position;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(name);
	_hit_box->SetHitBox(1, 1, 1);
	_i_player_data = new IPrayerData;
	_i_arm_data = new IArmData;
	_map_data = new IMapData;
	_effect_time = POWERUP_TIME;
	_player_speed = 0.05;
	_arm_speed = 0.1;
}

SpeedItem::~SpeedItem()
{
	delete _map_data;
	delete _i_arm_data;
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

	_model = ResouceManager::Instance().LoadModelFile(_T("Item/Itembox_v2.X"));

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
	if (_position.y <= 0)
		_position.y = 0;
	else
		_position.y -= 0.1;
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name    = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_tag = ARM_TAG + std::to_string(i + 1);

		if (_hit_box->IsHitObjectsSquare(name))
		{
			std::string status_name = "";
			int items_probability = MathHelper_Random(100);
			switch (_i_player_data->GetRankNum(name))
			{
			case 0:
				if (items_probability >= 34)
					status_name = ITEM_PLAYER_SPEEDUP;
				break;
			case 1:
				if (items_probability >= 77)
					status_name = ITEM_PLAYER_SPEEDUP;
				else if (items_probability >= 34)
					status_name = ITEM_ARM_SPEEDUP;
				break;
			case 2:
				if (items_probability >= 77)
					status_name = ITEM_PLAYER_SPEEDUP;
				else if (items_probability >= 34)
					status_name = ITEM_ARM_SPEEDUP;
				break;
			case 3:
				if (items_probability >= 50)
					status_name = ITEM_THUNDER;
				else if (items_probability >= 25)
					status_name = ITEM_PLAYER_SPEEDUP;
				else
					status_name = ITEM_ARM_SPEEDUP;
				break;
			}
			if (status_name == ITEM_PLAYER_SPEEDUP)
				_player_speed = 0.09;
			else if (status_name == ITEM_ARM_SPEEDUP)
				_arm_speed = 0.15;
			else if(status_name == "")
			{
				AudioManager::Instance().PowerDownPlay();
			}
			status_name = ITEM_THUNDER;
			if (status_name == ITEM_THUNDER)
			{
				_player_speed = 0.01;
				for (int i = 0; i < PLAYER_COUNT_MAX; i++)
				{
					std::string playertag = PLAYER_TAG + std::to_string(i + 1);
					if (playertag == name)
						continue;
					else
					{
						_effect_time = POWERDOWN_TIME;
						_hit_box->GetHitBoxTag(playertag)->GetPlayerBase()->GetItem(this, status_name);
					}
				}
				MainCamera::Instance().TimeReset();
			}
			else if(status_name != "")
			{
				_hit_box->GetHitBoxTag(name)->GetPlayerBase()->GetItem(this, status_name);
			}
			Removeflag = true;
			auto data = _map_data->GetData();

			int x = fabsf(_position.x);
			int z = fabsf(_position.z);

			data[z][x] = '?';
			_map_data->SetData(data);
		}
	}

	return 0;
}
