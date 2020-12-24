#include "Block.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/IData.h"
#include "../../../Data/WordsTable.h"
#include "../../../Managers/SceneManager/SceneManager.h"
#include "../../../ParticleSystem/Particle.h"

Block::Block(std::string tag)
{
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

	_handle = INT_MAX;

	if (_position.y > 0)
	{
		_blinking = new Blinking;
		_blinking->Initialize(_position);
	}

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
	if (_position.y > 0)
	{
		Fall();
	}

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string arm_tag    = ARM_TAG + std::to_string(i + 1);
		std::string player_tag = PLAYER_TAG + std::to_string(i + 1);

		if (!_hit_box->Tag_Sarch(arm_tag))
			continue;

		if (_hit_box->IsHitObjectsSquare(arm_tag)) 
		{
			IArmData* arm_data = new IArmData;
			int state = arm_data->GetState(arm_tag);
			if (state == ArmEnum::PunchState::RETURN_PUNCH)
			{
				delete arm_data;
				return 0;
			}

			IMapData* map_data = new IMapData;
			auto data = map_data->GetData();

			int x = fabsf(_position.x);
			int z = fabsf(_position.z);

			data[z][x] = ' ';
			map_data->SetData(data);
			delete map_data;

			arm_data->SetState(arm_tag, ArmEnum::PunchState::RETURN_PUNCH);
			delete arm_data;

			IPrayerData* player_data = new IPrayerData;
			player_data->SetRankingPoint(player_tag, player_data->GetRankingPoint(player_tag) + 10);
			delete player_data;

			_effect->SetPosition(_position + Vector3_Up * 0.5f);
			_effect->PlayOneShot();

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
	if (_position.y > 0)
	{
		_blinking->Draw3D();
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
/**
 * @fn 降ってくるときのブロックの処理
 * @detail  ブロックを下に動かす
 *          ブロックのY座標が0になった時mapdataに自分の座標を保存する
 *          プレイヤーとの接触時にプレイヤーを倒す
 */
void Block::Fall()
{
	//TODO:降ってくる速さは調整する
	_position.y -= 0.05;

	//!Y座標が0になったときに自分の座標をマップデータをセットする
	if (_position.y <= 0)
	{
		IMapData* map_data = new IMapData;
		auto data = map_data->GetData();

		int x = fabsf(_position.x);
		int z = fabsf(_position.z);

		data[z][x] = 'b';
		map_data->SetData(data);
		delete map_data;
		delete _blinking;
	}

	_hit_box->SetHitBoxPosition(_position + Vector3(0, 1, 0));

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string player_tag = PLAYER_TAG + std::to_string(i + 1);

		//!プレイヤーとの接触時にプレイヤーを倒す
		if (_hit_box->IsHitObjectsSquare(player_tag))
		{
			IPrayerData* iplayerdata = new IPrayerData;
			iplayerdata->SetState(player_tag, PlayerEnum::Animation::DEATH);
			delete iplayerdata;
		}

	}
	_blinking->Update();
}