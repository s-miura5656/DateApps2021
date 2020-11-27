#include"WallCorner.h"

WallCorner::WallCorner()
{
	_model = nullptr;
}

WallCorner::~WallCorner()
{

}

bool WallCorner::Initialize()
{
	//Xファイルの読み込み
	_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/wal_corner.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());
	return _model != nullptr;
}