#include"Block.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"

Block::Block(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_tag = tag;
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(1.f);
}

Block::~Block()
{
	_hit_box.reset();
}

bool Block::Initialize()
{
	//Xファイルの読み込み
	//_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/capsule.X"));
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/capsule.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());
	//当たり判定を破壊可能ブロックと同じポジションにする
	_hit_box->SetHitBoxPosition(_position);
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
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		if (_hit_box->IsHitObjects(name))
		{
			return 1;
		}
	}

	return 0;
}
