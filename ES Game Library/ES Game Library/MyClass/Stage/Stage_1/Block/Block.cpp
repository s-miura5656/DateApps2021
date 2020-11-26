#include"Block.h"
#include "../../../Managers/ResouceManager/ResouceManager.h"

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
	//_model = GraphicsDevice.CreateModelFromFile(_T("MapSprite/capsule.X"));
	_model = ResouceManager::Instance().LoadModelFile(_T("MapSprite/capsule.X"));
	//スケールの設定
	_model->SetScale(_scale);
	//マテリアルの設定
	_model->SetMaterial(GetMaterial());
	return _model != nullptr;
}

void Block::Draw3D()
{
	if (_destructiveflag)
	{
		StageBase::Draw3D();
	}
}

