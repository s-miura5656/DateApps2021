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
		//SpriteBatch.DrawString(_font, Vector2(0, 250), Color(1.f, 1.f, 1.f), _T("ANGLE:%f"), _angle);
		//SpriteBatch.DrawString(_font, Vector2(0, 350), Color(1.f, 1.f, 1.f), _T("POS_X:%f"), _iplayer_data->GetPosition(_tag).x);
		//SpriteBatch.DrawString(_font, Vector2(0, 400), Color(1.f, 1.f, 1.f), _T("POS_Z:%f"), _iplayer_data->GetPosition(_tag).z);
	}

	if (_arm != nullptr)
		_arm->Draw2D();
}

void PlayerBase::Draw3D()
{
	_model->SetPosition(_iplayer_data->GetPosition(_tag));
	_model->SetRotation(Vector3(0, _angle - 180, 0));
	_model->AdvanceTime(GameTimer.GetElapsedSecond() * 2);
	_model->Draw();
	_model->SetRotation(Vector3(0, _angle, 0));

	auto collision_pos = _model->GetPosition();
	collision_pos.y += _model->GetScale().y / 2;
	_hit_box->SetHitBoxPosition(collision_pos);
	_hit_box->Draw3D();

	if (_arm != nullptr)
		_arm->Draw3D();
}

void PlayerBase::ChangeAnimation()
{
	auto&& state = _iplayer_data->GetState(_tag);

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
	auto&& map_data = _imap_data->GetData();

	if (_move_flag)
	{
		_position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
		_lerp_count += _iplayer_data->GetSpeed(_tag);

		if (_lerp_count >= 1.f)
		{
			_move_flag = false;
			_lerp_count = 0;
			_iplayer_data->SetState(_tag, PlayerEnum::Animation::WAIT);
		}
	}
	else
	{
		float abs_x = fabsf(pad->GetPadStateX());

		float abs_z = fabsf(pad->GetPadStateY());

		if (abs_x > abs_z)
		{
			int old_index = _index_num.x;

			std::signbit(pad->GetPadStateX()) ? _index_num.x-- : _index_num.x++;

			_index_num.x = Clamp(_index_num.x, 1, map_data[_index_num.z].size() - 3);

			if (map_data[_index_num.z][_index_num.x] != 'i' &&
				map_data[_index_num.z][_index_num.x] != 'w' &&
				map_data[_index_num.z][_index_num.x] != 'b')
			{
				_new_pos = Vector3(1 * _index_num.x, 0, 1 * -_index_num.z);
				_move_flag = true;
			}
			else
			{
				_index_num.x = old_index;
			}
		}

		if (abs_x < abs_z)
		{
			int old_index = _index_num.z;

			std::signbit(pad->GetPadStateY()) ? _index_num.z-- : _index_num.z++;

			_index_num.z = Clamp(_index_num.z, 1, map_data.size() - 2);

			if (map_data[_index_num.z][_index_num.x] != 'i' &&
				map_data[_index_num.z][_index_num.x] != 'w' &&
				map_data[_index_num.z][_index_num.x] != 'b')
			{
				_new_pos = Vector3(1 * _index_num.x, 0, 1 * -_index_num.z);
				_iplayer_data->SetIndexNum(_tag, _index_num);
				_move_flag = true;
			}
			else
			{
				_index_num.z = old_index;
			}
		}

		_old_pos = _position;
	}

	_model->SetPosition(_position);
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


