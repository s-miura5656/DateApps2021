#include"Block.h"

Block::Block()
{
	block_base = nullptr;
}

Block::~Block()
{

}

bool Block::Initialize()
{
	//Xファイルの読み込み
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/block.X"));
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

