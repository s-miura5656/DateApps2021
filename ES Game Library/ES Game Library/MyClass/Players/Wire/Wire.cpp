#include "Wire.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include "../../Data/MyAlgorithm.h"

Wire::Wire(std::string arm_tag)
{
	_arm_tag = arm_tag;

	_i_arm_data = std::make_unique<IArmData>();
}

Wire::~Wire()
{
	_i_arm_data.reset();
}

bool Wire::Initialize()
{
	_model  = ResouceManager::Instance().LoadModelFile(_T("Player/wire.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));

	auto arm_positions = _i_arm_data->GetAnglePositions(_arm_tag);
	auto arm_angles	   = _i_arm_data->GetAngles(_arm_tag);

	_transform.position   = *arm_positions.end();
	_transform.rotation	  = Vector3_Zero;
	_transform.rotation.y = *arm_angles.end();
	_transform.scale	  = Vector3_One;

	auto path = ConvertFilePath("Player/", "wire", ".png");
	_texture = ResouceManager::Instance().LordSpriteFile(path.c_str());

	_material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	_material.Ambient  = Color(1.0f, 1.0f, 1.0f);
	_material.Specular = Color(1.0f, 1.0f, 1.0f);

	return true;
}

int Wire::Update()
{
	

	return 0;
}

void Wire::Draw3D()
{
	auto camera = SceneCamera::Instance().GetCamera();

	_model->SetMaterial(_material);

	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetParameter("model_ambient", _material.Ambient);
	_shader->SetParameter("eye_pos", camera.GetPosition());

	Matrix vp = camera->GetViewProjectionMatrix();

}

