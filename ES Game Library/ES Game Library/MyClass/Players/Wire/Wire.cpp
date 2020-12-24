#include "Wire.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include "../../Data/MyAlgorithm.h"

Wire::Wire(Transform arm_transform)
{
	_transform = arm_transform;
}

Wire::~Wire()
{
	_effect.reset();
	auto i_map_data = new IMapData;
	
	auto data = i_map_data->GetData();

	int x = fabsf(_transform.position.x);
	int z = fabsf(_transform.position.z);

	if (data[z][x] == 'd')
	{
		data[z][x] = ' ';
	}

	i_map_data->SetData(data);
	delete i_map_data;
}

bool Wire::Initialize()
{
	_effect = std::make_unique<ParticleSystem>();

	_material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	_material.Ambient  = Color(1.0f, 1.0f, 1.0f);
	_material.Specular = Color(1.0f, 1.0f, 1.0f);

	auto i_map_data = new IMapData;

	auto data = i_map_data->GetData();

	int x = fabsf(_transform.position.x);
	int z = fabsf(_transform.position.z);

	if (data[z][x] == ' ')
	{
		data[z][x] = 'd';
	}

	i_map_data->SetData(data);
	delete i_map_data;

	auto&& effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/wire/wire.efk"));
	_effect->RegisterParticle(effect);
	_effect->SetSpeed(1.0f);
	_effect->SetScale(1.0f);
	_effect->SetRotation(_transform.rotation);
	_effect->SetPosition(_transform.position);
	_effect->PlayOneShot();

	return true;
}

void Wire::Draw3D()
{
	_effect->Draw();
}

