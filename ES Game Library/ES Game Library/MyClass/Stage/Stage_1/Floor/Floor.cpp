
#include"Floor.h"
Floor::Floor()
{
	_model = nullptr;
}

Floor::~Floor()
{

}

bool Floor::Initialize()
{
	//Xファイルの読み込み
	_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/stage.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());
	
	return _model != nullptr;
}