#include"Metal.h"

Metal::Metal()
{
	block_base = nullptr;
}

Metal::~Metal()
{

}

bool Metal::Initialize()
{
	//Xファイルの読み込み
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/metal.X"));
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