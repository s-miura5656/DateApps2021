#include "PlayerBase.h"

PlayerBase::PlayerBase()
{
}

PlayerBase::~PlayerBase()
{
}

bool PlayerBase::FileInitialize(LPCTSTR& file)
{
	player = GraphicsDevice.CreateModelFromFile(file);
	rocket_punch = GraphicsDevice.CreateModelFromFile(_T("Player/sword_01.X"));
	return true;
}

void PlayerBase::Draw2D()
{
}

void PlayerBase::Draw3D()
{
	player->Draw();

	rocket_punch->Draw();
}
