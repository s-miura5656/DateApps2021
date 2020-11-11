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
	block_base = GraphicsDevice.CreateModelFromFile(_T("MapSprite/Pillar.X"));
	block_base->SetScale(scale);
	block_base->SetMaterial(GetMaterial());
	if (nullptr == block_base)
	{
		return false;
	}
	return true;
}