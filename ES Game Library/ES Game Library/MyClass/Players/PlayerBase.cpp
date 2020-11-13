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

void PlayerBase::ChangePlayerSpeed()
{
	auto data = _iplayer_data;

	if (_move_speed == data->GetSpeed(_tag) && _weight == data->GetWeight(_tag))
		return;

	_move_speed = (float)data->GetSpeed(_tag) / (float)data->GetWeight(_tag);

	_move_speed /= 100.f;

	_move_speed *= 5.f;
}
