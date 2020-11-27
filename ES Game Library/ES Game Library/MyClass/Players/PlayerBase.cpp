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
		SpriteBatch.DrawString(_font, Vector2(0, 250), Color(1.f, 1.f, 1.f), _T("ANGLE:%f"), _angle);
		//SpriteBatch.DrawString(_font, Vector2(0, 350), Color(1.f, 1.f, 1.f), _T("POS_X:%f"), _iplayer_data->GetPosition(_tag).x);
		//SpriteBatch.DrawString(_font, Vector2(0, 400), Color(1.f, 1.f, 1.f), _T("POS_Z:%f"), _iplayer_data->GetPosition(_tag).z);
	}
	if (_arm != nullptr)
	{
		_arm->Draw2D();
	}
}

void PlayerBase::Draw3D()
{
	_model->SetPosition(_iplayer_data->GetPosition(_tag));
	_model->SetRotation(Vector3(15, _angle - 180, 0));
	_model->Draw();
	_model->SetRotation(Vector3(0, _angle, 0));

	auto collision_pos = _model->GetPosition();
	collision_pos.y = _model->GetScale().y / 2;
	_hit_box->SetHitBoxPosition(collision_pos);
	_hit_box->Draw3D();

	if (_arm != nullptr)
	{
		_arm->Draw3D();
	}
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

void PlayerBase::CreateArm()
{
	if (_arm != nullptr)
		_arm = nullptr;

	_arm = new Arm(_tag);
	_arm->Initialize();
}

void PlayerBase::DestroyArm()
{
	if (_arm == nullptr)
		return;

	_arm = nullptr;
}


