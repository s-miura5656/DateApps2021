#include "Block.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/IData.h"
#include "../../../Data/WordsTable.h"
#include "../../../Managers/SceneManager/SceneManager.h"
#include "../../../ParticleSystem/Particle.h"

Block::Block(std::string tag, std::string item)
{
	_item_name = item;
	_model  = nullptr;
	_tag = tag;
}

Block::~Block()
{
	_hit_box.reset();
	_effect.reset();
}

bool Block::Initialize()
{
	_effect.reset(new ParticleSystem);
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(1.0f);

	//Xファイルの読み込み
	_model  = ResouceManager::Instance().LoadModelFile(_T("MapSprite/capsule2.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StandardShader.hlsl"));
	auto effect = ResouceManager::Instance().LordEffekseerFile(_T("Effect/effekseer_break02/break_effect.efk"));

	_effect->RegisterParticle(effect);
	_effect->SetSpeed(1.0f);
	_effect->SetScale(1.0f);

	//スケールの設定
	_scale = 0.85f;
	_model->SetScale(_scale);
	//マテリアルの設定
	
	//当たり判定を破壊可能ブロックと同じポジションにする
	_hit_box->SetHitBoxPosition(_position + Vector3(0, 1, 0));

	//! shader
	_shader->SetParameter("light_dir", SceneLight::Instance().GetLight().Direction);
	return _model != nullptr;
}
/**
 * @brief プレイヤーが触れた時の処理
 * @return プレイヤーが触れてない時 (int)0
 * @return プレイヤーが触れた時 (int)1
 */
int Block::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string arm_tag    = ARM_TAG + std::to_string(i + 1);

		float distance = Vector3_Distance(_i_arm_data->GetPosition(arm_tag), _position);

		if (distance > _arm_distance)
			continue;

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

			std::unique_ptr<IMapData> map_data = std::make_unique<IMapData>();
			auto data = map_data->GetData();

			int x = fabsf(_position.x);
			int z = fabsf(_position.z);

			data[z][x] = ' ';
			map_data->SetData(data);

			arm_data->SetState(arm_tag, ArmEnum::PunchState::RETURN_PUNCH);

			std::unique_ptr<IPrayerData> player_data = std::make_unique<IPrayerData>();
			std::string player_tag = PLAYER_TAG + std::to_string(i + 1);
			//player_data->SetRankingPoint(player_tag, player_data->GetRankingPoint(player_tag) + BLOCK_POINT);

			_effect->SetPosition(_position + Vector3_Up * 0.5f);
			_effect->PlayOneShot();

			//!アイテムが入ってないブロックの時はアイテムを生成しない
			if (_item_name != NULL_ITEM_TAG)
			{
				ItemCounter::SetItem(_item_name, _position,BLOCK_POINT);
			}

			return 1;
		}
	}
	return 0;
}

void Block::Draw3D()
{
	if (_hit_box != nullptr)
	{
		_hit_box->SetModelPosition();
		_hit_box->SetModelScale();
		//_hit_box->Draw3D();
	}

	_effect->Draw();
}

void Block::DrawAlpha3D()
{
	Material mat;
	mat.Diffuse = Color(0.5f, 0.5f, 0.5f);
	mat.Ambient = Color(1.0f, 1.0f, 1.0f);
	mat.Specular = Color(0.5f, 0.5f, 0.5f);

	_model->SetMaterial(mat);
	_model->SetPosition(_position);
	_model->SetRotation(0, 0, 0);

	Matrix world = _model->GetWorldMatrix();
	_shader->SetParameter("model_ambient", _model->GetMaterial().Ambient);
	_shader->SetParameter("wvp", world * SceneCamera::Instance().GetCamera().GetViewProjectionMatrix());
	_shader->SetParameter("eye_pos", SceneCamera::Instance().GetCamera().GetPosition());
	_shader->SetTechnique("FixModel_S0");

	_model->Draw(_shader);
}