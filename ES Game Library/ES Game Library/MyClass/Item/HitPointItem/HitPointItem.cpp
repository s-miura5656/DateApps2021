#include "HitPointItem.h"
#include "../../Data/GameData.h"

HitPointItem::HitPointItem(Vector3 position, std::string name)
{
	this->_position = position;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(name);
	_hit_box->SetHitBox(1, 1, 1);
	_iplayer_data = new IPrayerData;

	_rotation = 0.0f;
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
	_rotation += 1.0f;
	if (_rotation >= 360.0f)
		_rotation -= 360.0f;

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		if (_hit_box->IsHitObjects(name))
		{
			ItemEffect(name);
			return END;
		}
	}

	Removeflag = true;

	return 0;
}

void HitPointItem::Draw3D()
{
	Matrix rotation = Matrix_CreateFromYawPitchRoll(0.0f, 45.0f, 45.0f);
	rotation *= Matrix_CreateRotationY(_rotation);
	_box->SetDirection(Quaternion_CreateFromRotationMatrix(rotation));

	ItemBase::Draw3D();
}