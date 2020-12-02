#include "PlayerBase.h"
#include "../Data/MyAlgorithm.h"

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
		SpriteBatch.DrawString(_font, Vector2(0, 200), Color(1.f, 0.f, 0.f), _T("�v���C���[��HP:%f"), _i_player_data->GetHitPoint(_tag));
		SpriteBatch.DrawString(_font, Vector2(0, 250), Color(1.f, 0.f, 0.f), _T("�v���C���[�̈ړ����x:%f"), _i_player_data->GetSpeed(_tag));
	}

	if (_arm_tag == "Arm_1")
	{
		SpriteBatch.DrawString(_font, Vector2(0, 300), Color(1.f, 0.f, 0.f), _T("�A�[���̔�ԑ��x:%f"), _i_arm_Data->GetGoSpeed(_arm_tag));
		SpriteBatch.DrawString(_font, Vector2(0, 350), Color(1.f, 0.f, 0.f), _T("�A�[���̖߂鑬�x:%f"), _i_arm_Data->GetReturnSpeed(_arm_tag));
		SpriteBatch.DrawString(_font, Vector2(0, 400), Color(1.f, 0.f, 0.f), _T("�A�[���̍ő勗��:%d"), _i_arm_Data->GetLimitRange(_arm_tag));
	}

	if (_arm != nullptr)
		_arm->Draw2D();
}

void PlayerBase::Draw3D()
{
	_model->SetPosition(_position);
	_model->SetRotation(Vector3(0, _angle - 180, 0));
	_model->AdvanceTime(GameTimer.GetElapsedSecond() * 2);
	_model->Draw();
	_model->SetRotation(Vector3(0, _angle, 0));
	
	_i_player_data->SetAngle(_tag, _angle);
	_i_player_data->SetPosition(_tag, _position);

	auto collision_pos = _model->GetPosition();
	collision_pos.y += _model->GetScale().y / 2;
	_hit_box->SetHitBoxPosition(collision_pos);
	_hit_box->Draw3D();

	if (_arm != nullptr)
		_arm->Draw3D();
}

void PlayerBase::ChangeAnimation()
{
	int state = _i_player_data->GetState(_tag);

	for (int i = 0; i < PlayerEnum::Animation::ANIMATION_ALL_TYPE; ++i)
	{
		if (i == state)
		{
			_model->SetTrackEnable(i, TRUE);
			continue;
		}

		_model->SetTrackEnable(i, FALSE);
	}
}

void PlayerBase::Move(Controller* pad)
{
	auto&& map_data = _i_map_data->GetData();

	if (_move_flag)
	{
		_position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
		_lerp_count += _i_player_data->GetSpeed(_tag);

		_lerp_count = Clamp(_lerp_count, 0, 1.f);

		if (_lerp_count >= 1.f) 
		{
			_move_flag  = false;
			_lerp_count = 0;
			_i_player_data->SetPosition(_tag, _position);
		}
	}
	else
	{
		float abs_x = fabsf(pad->GetPadStateX());
		float abs_z = fabsf(pad->GetPadStateY());
		
		int old_index_x = _index_num.x;
		int old_index_z = _index_num.z;

		if (abs_x > abs_z)
		{
			std::signbit(pad->GetPadStateX()) ? _index_num.x-- : _index_num.x++;

			_index_num.x = (int)Clamp(_index_num.x, 1, map_data[_index_num.z].size() - 3);
		}
		else if (abs_x < abs_z)
		{
			std::signbit(pad->GetPadStateY()) ? _index_num.z-- : _index_num.z++;

			_index_num.z = (int)Clamp(_index_num.z, 1, map_data.size() - 2);
		}

		if (map_data[_index_num.z][_index_num.x] != 'i' &&
			map_data[_index_num.z][_index_num.x] != 'w' &&
			map_data[_index_num.z][_index_num.x] != 'b')
		{
			_new_pos = Vector3(1 * _index_num.x, 0, 1 * -_index_num.z);
			_i_player_data->SetIndexNum(_tag, _index_num);
			_move_flag = true;
		}
		else
		{
			_index_num.x = old_index_x;
			_index_num.z = old_index_z;
		}

		_old_pos = _position;
	}
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

	delete _arm;
	_arm = nullptr;
}


