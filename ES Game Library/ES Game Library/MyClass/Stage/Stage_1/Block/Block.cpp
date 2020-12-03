#include "Block.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/IData.h"
#include "../../../Data/WordsTable.h"
#include "../../../Managers/SceneManager/SceneManager.h"

Block::Block(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_tag = tag;
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(1.0f);
}

Block::~Block()
{
	_hit_box.reset();
}

bool Block::Initialize()
{
	//Xファイルの読み込み
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/capsule.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/StageShader.hlsl"));

	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());
	//当たり判定を破壊可能ブロックと同じポジションにする
	_hit_box->SetHitBoxPosition(_position + Vector3(0,1,0));

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
		std::string arm_tag = ARM_TAG + std::to_string(i + 1);
		
		if (!_hit_box->Tag_Sarch(arm_tag))
			continue;

		if (_hit_box->IsHitObjectsSquare(arm_tag)) 
		{
			IMapData* map_data = new IMapData;
			auto data = map_data->GetData();

			int x = fabsf(_position.x);
			int z = fabsf(_position.z);

			data[z][x] = ' ';
			map_data->SetData(data);
			delete map_data;

			IArmData* arm_data = new IArmData;
			arm_data->SetState(arm_tag, ArmEnum::PunchState::RETURN_PUNCH);
			delete arm_data;
			return 1;
		}
	}

	return 0;
}

void Block::Draw3D()
{
	_model->SetPosition(_position);
	_model->SetRotation(0, 0, 0);
	Matrix world = _model->GetWorldMatrix();
	_shader->SetParameter("wvp", world * SceneCamera::Instance().GetCamera().GetViewProjectionMatrix());

	GraphicsDevice.BeginAlphaBlend();
	GraphicsDevice.SetRenderState(CullMode_None);
	_model->Draw(_shader);
	GraphicsDevice.SetRenderState(CullMode_CullCounterClockwiseFace);
	GraphicsDevice.EndAlphaBlend();

	if (_hit_box != nullptr)
	{
		//_hit_box->Draw3D();
	}
}
