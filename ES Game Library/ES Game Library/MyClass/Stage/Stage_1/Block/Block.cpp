#include "Block.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/IData.h"

Block::Block(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_tag = tag;
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(0.9f);
}

Block::~Block()
{
	_hit_box->OnReMove();
}

bool Block::Initialize()
{
	//Xファイルの読み込み
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/capsule.X"));
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

		if (_hit_box->IsHitObjects(arm_tag)) 
		{
			IMapData* mapdata = new IMapData;
			auto data = mapdata->GetData();

			int x = fabsf(_position.x);
			int z = fabsf(_position.z);

			data[z][x] = ' ';
			mapdata->SetData(data);
			delete mapdata;
			return 1;
		}
	}
	return 0;
}
