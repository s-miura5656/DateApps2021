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
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/metal.X"));
	block_base->SetScale(scale);
	block_base->SetMaterial(GetMaterial());
	if (nullptr == block_base)
	{
		return false;
	}
	return true;
}