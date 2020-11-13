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

float PlayerBase::PlayerSpeed()
{
	auto p_data = _iplayer_data;

	auto a_data = _iarm_data;

	if (_weight != p_data->GetWeight(_tag))
	{
		_weight = p_data->GetWeight(_tag) + a_data->GetWeight(_arm_tag);
		_iplayer_data->SetWeight(_tag, _weight);
		_move_speed = (float)p_data->GetSpeed(_tag) / (float)p_data->GetWeight(_tag);
	}

	if (_speed != p_data->GetSpeed(_tag))
	{
		_move_speed = (float)p_data->GetSpeed(_tag) / (float)p_data->GetWeight(_tag);
	}

	_move_speed /= 100.f;

	_move_speed *= 5.f;

	return _move_speed;
}
