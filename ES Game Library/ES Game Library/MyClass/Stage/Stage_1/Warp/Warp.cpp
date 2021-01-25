#include"Warp.h"
#include "../../../Data/WordsTable.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"

Warp::Warp(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_tag = tag;
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(1.0f);
}

Warp::~Warp()
{
	_hit_box.reset();
}

bool Warp::Initialize()
{
	//Xファイルの読み込み
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/warp.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());

	_hit_box->SetHitBoxPosition(_position);

	flag = false;
	return _model != nullptr;
}
int Warp::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string player_tag = PLAYER_TAG + std::to_string(i + 1);

		if (!_hit_box->Tag_Sarch(player_tag))
			continue;

		if (_hit_box->IsHitObjectsSquare(player_tag))
		{
			flag = true;
			return 0;
		}
		else {
			flag = false;
		}
	}

	return 0;
}

void Warp::Draw3D()
{
	_model->SetPosition(_position);
	//_model->Draw();
}
