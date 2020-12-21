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
	_model  = ResouceManager::Instance().LoadModelFile(_T("Player/wire.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));

	auto path = ConvertFilePath("Player/", "wire", ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());

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

	return true;
}

void Wire::Draw3D()
{
	auto camera = SceneCamera::Instance().GetCamera();

	_model->SetMaterial(_material);
	_model->SetPosition(_transform.position);
	_model->SetRotation(_transform.rotation);

	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetParameter("model_ambient", _material.Ambient);
	_shader->SetParameter("eye_pos", camera.GetPosition());

	Matrix vp = camera->GetViewProjectionMatrix();
	Matrix world = _model->GetWorldMatrix();
	_shader->SetParameter("wvp", world * vp);

	_shader->SetParameter("limit_color", Vector3(0.0f, 1.0f, 0.0f));
	_shader->SetTechnique("FixLimitModel_S1");
	_model->Draw(_shader);
}

