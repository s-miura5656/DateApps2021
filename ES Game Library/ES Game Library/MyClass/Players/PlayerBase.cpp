#include "PlayerBase.h"

PlayerBase::PlayerBase()
{
}

PlayerBase::~PlayerBase()
{
}

void PlayerBase::Draw2D()
{
	if (_tag == "Player_1")
	{
		//SpriteBatch.DrawString(_font, Vector2(0, 250), Color(1.f, 1.f, 1.f), _T("DISTANCE:%f"), _hit_box->_dist);
		SpriteBatch.DrawString(_font, Vector2(0, 350), Color(1.f, 1.f, 1.f), _T("POS_X:%f"), _iplayer_data->GetPosition(_tag).x);
		SpriteBatch.DrawString(_font, Vector2(0, 400), Color(1.f, 1.f, 1.f), _T("POS_Z:%f"), _iplayer_data->GetPosition(_tag).z);
	}
}

void PlayerBase::Draw3D()
{
	_player->SetPosition(_iplayer_data->GetPosition(_tag));
	_player->Draw();
	
	_arm->Draw();

	auto collision_pos = _player->GetPosition();
	collision_pos.y = _player->GetScale().y / 2;
	_hit_box->SetHitBoxPosition(collision_pos);
	_hit_box->Draw3D();
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
