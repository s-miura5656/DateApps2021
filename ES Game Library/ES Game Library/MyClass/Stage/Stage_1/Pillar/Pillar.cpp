#include"Pillar.h"

Pillar::Pillar()
{
	_model = nullptr;
}

Pillar::~Pillar()
{

}

bool Pillar::Initialize()
{
	//Xファイルの読み込み
	_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/Pillar.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());
	
	return _model != nullptr;
}