#include "HitPointItem.h"
#include "../../Data/WordsTable.h"

HitPointItem::HitPointItem(Vector3 position, std::string name)
{
	this->_position = position;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(name);
	_i_player_data = new IPrayerData;
}

HitPointItem::~HitPointItem()
{
	delete _i_player_data;
	_hit_box.reset();
}


bool HitPointItem::Initialize()
{
	_hit_point = 1000.f;

	_model = ResouceManager::Instance().LoadModelFile(_T("Item/Weakened_item.X"));
	_model->SetScale(_scale);
	Material material;
	material.Diffuse = Color(1.0f, 1.0f, 1.0f);
	material.Ambient = Color(1.0f, 1.0f, 1.0f);

	BoxShape(5);

	_model->SetMaterial(material);
	
	return true;
}

int HitPointItem::Update()
{
	RotationItem();

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name    = PLAYER_TAG + std::to_string(i + 1);
		std::string arm_tag = ARM_TAG + std::to_string(i + 1);
		if (_hit_box->IsHitObjectsSquare(name))
		{
			//ItemEffect(name);
			_i_player_data->SetParameter_Change_Flag(name, true);
			_i_player_data->SetSpeed(name, 0.01);
			_i_arm_data->SetGoSpeed(arm_tag, 0.02);
			Removeflag = true;
		}
	}

	return 0;
}
