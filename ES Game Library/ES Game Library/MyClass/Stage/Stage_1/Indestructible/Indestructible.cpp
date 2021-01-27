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

	_position.y += -0.1;
	if (_position.y <= 0)
	{
		std::unique_ptr<IMapData> map_data = std::make_unique<IMapData>();
		auto data = map_data->GetData();

		int x = fabsf(_position.x);
		int z = fabsf(_position.z);

		data[z][x] = 'i';
		map_data->SetData(data);
		_position.y = 0;
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
