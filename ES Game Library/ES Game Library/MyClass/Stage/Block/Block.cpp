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
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/block.X"));
	block_base->SetScale(scale);
	block_base->SetMaterial(GetMaterial());
	if (nullptr == block_base)
	{
		return false;
	}
	return true;
}

