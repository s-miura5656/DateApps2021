#include"Block.h"

Block::Block()
{
	_model = nullptr;
}

Block::~Block()
{

}

bool Block::Initialize()
{
	//Xファイルの読み込み
	_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/block.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());

	return _model != nullptr;
}

