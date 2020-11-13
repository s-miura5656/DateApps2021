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
	auto collision_pos = player->GetPosition();
	collision_pos.y = player->GetScale().y / 2;
	_hit_box->SetHitBoxPosition(collision_pos);

	player->Draw();
	_hit_box->Draw3D();
	arm->Draw();
}
