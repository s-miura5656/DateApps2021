#include"Metal.h"

Metal::Metal()
{
	_model = nullptr;
}

Metal::~Metal()
{

}

bool Metal::Initialize()
{
	//Xファイルの読み込み
	_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/metal.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());
	
	return _model != nullptr;
}