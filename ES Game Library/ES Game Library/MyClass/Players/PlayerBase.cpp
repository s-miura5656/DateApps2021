#include "PlayerBase.h"

PlayerBase::PlayerBase()
{
}

PlayerBase::~PlayerBase()
{
}

void PlayerBase::Draw2D()
{
}

void PlayerBase::Draw3D()
{
	player->Draw();

	arm->Draw();
}
