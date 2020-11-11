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
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/ground.X"));
	block_base->SetScale(scale);
	block_base->SetMaterial(GetMaterial());
	if (nullptr == block_base)
	{
		return false;
	}
	return true;
}