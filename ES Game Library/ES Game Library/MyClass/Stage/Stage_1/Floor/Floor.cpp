
#include"Floor.h"
Floor::Floor()
{
	block_base = nullptr;
}

Floor::~Floor()
{

}

bool Floor::Initialize()
{
	//Xファイルの読み込み
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/ground.X"));
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