#include"RotatingFloor .h"
#include"../../../Managers/ResouceManager/ResouceManager.h"
#include "../../../Data/WordsTable.h"
RotatingFloor::RotatingFloor(std::string tag)
{
	_model = nullptr;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_tag = tag;
	_hit_box->Settags(_tag);
	_hit_box->SetHitBoxScale(1.0f);
}

RotatingFloor::~RotatingFloor()
{

}

bool RotatingFloor::Initialize()
{
	//Xファイルの読み込み
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/arrow_1.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());

	_hit_box->SetHitBoxPosition(_position);
	return _model != nullptr;
}
int RotatingFloor::Update()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		std::string player_tag = PLAYER_TAG + std::to_string(i + 1);

		if (!_hit_box->Tag_Sarch(player_tag))
			continue;

		if (_hit_box->IsHitObjectsSquare(player_tag))
		{
			rotation += 90;
			return 0;
		}
	}
	return 0;
}
void RotatingFloor::Draw3D()
{
	_model->SetPosition(_position);
	_model->SetRotation(0, rotation, 0);
	_model->Draw();
}