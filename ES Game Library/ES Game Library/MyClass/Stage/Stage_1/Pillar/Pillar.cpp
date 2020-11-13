#include"Pillar.h"

Pillar::Pillar()
{
	block_base = nullptr;
}

Pillar::~Pillar()
{

}

bool Pillar::Initialize()
{
	//Xファイルの読み込み
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/Pillar.X"));
	//スケールの設定
	block_base->SetScale(scale);
	//マテリアルの設定
	block_base->SetMaterial(GetMaterial());
	if (nullptr == block_base)
	{
		return false;
	}
	return true;
}