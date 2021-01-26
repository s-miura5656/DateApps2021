#include"Indestructible.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Managers/SceneManager/SceneManager.h"
#include "../../../Managers/AudioManager/AudioManager.h"
Indestructible::Indestructible(std::string tag)
{
	_tag = tag;
	_model = nullptr;
}

Indestructible::~Indestructible()
{
	_hit_box.reset();
}

bool Indestructible::Initialize()
{
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(1.0f);
	//Xファイルの読み込み
	_model  = ResouceManager::Instance().LoadModelFile(_T("MapSprite/Indestructible.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));

	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定

	_model_material.Diffuse  = Color(1.0f, 1.0f, 1.0f);
	_model_material.Ambient  = Color(0.25f, 0.25f, 0.25f);
	_model_material.Specular = Color(1.0f, 1.0f, 1.0f);
	
	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);

	return _model != nullptr;
}

int Indestructible::Update()
{
	//当たり判定を破壊可能ブロックと同じポジションにする
	if (_hit_box != nullptr)
	_hit_box->SetHitBoxPosition(_position + Vector3(0, 1, 0));
	if (_position.x >= 13)
	{
		_speed *= -1;
	}
	else if(_position.x <= 1)
	{
		_speed *= -1;
	}
	_position.x += _speed;
	if (_position.x < 1)
	{
		_position.x = 1;
	}
	if (_position.x > 13)
	{
		_position.x = 13;
	}
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string arm_tag = ARM_TAG + std::to_string(i + 1);

		float distance = Vector3_Distance(_i_arm_data->GetPosition(arm_tag), _position);

		if (!_hit_box->Tag_Sarch(arm_tag))
			continue;

		if (_hit_box->IsHitObjectsSquare(arm_tag))
		{
			std::unique_ptr<IArmData> arm_data = std::make_unique<IArmData>();
			int state = arm_data->GetState(arm_tag);

			if (state == ArmEnum::PunchState::RETURN_PUNCH)
			{
				return 0;
			}

			arm_data->SetState(arm_tag, ArmEnum::PunchState::RETURN_PUNCH);
		}
	}
	return 0;
}

void Indestructible::Draw3D()
{
	if (_hit_box != nullptr)
	{
		_hit_box->SetModelPosition();
		_hit_box->SetModelScale();
		//_hit_box->Draw3D();
	}
	_model->SetPosition(_position);
	_model->SetRotation(0, 0, 0);
	_model->SetMaterial(_model_material);

	auto camera = SceneCamera::Instance().GetCamera();
	Matrix world = _model->GetWorldMatrix();
	_shader->SetParameter("model_ambient", _model_material.Ambient);
	_shader->SetParameter("wvp", world * camera.GetViewProjectionMatrix());
	_shader->SetParameter("eye_pos", camera.GetPosition());
	_shader->SetTechnique("FixModel_S0");
	_model->Draw(_shader);
}
