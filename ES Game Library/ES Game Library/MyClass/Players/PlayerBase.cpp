#include "PlayerBase.h"
#include "../Data/MyAlgorithm.h"
#include "../Managers/SceneManager/SceneManager.h"

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
		SpriteBatch.DrawString(_font, Vector2(0, 180), Color(1.f, 1.f, 1.f), _T("プレイヤーのキル数:%d"), _i_player_data->GetKillCount(_tag));
		SpriteBatch.DrawString(_font, Vector2(0, 200), Color(1.f, 1.f, 1.f), _T("プレイヤーのHP:%d"), _i_player_data->GetHitPoint(_tag));
		SpriteBatch.DrawString(_font, Vector2(0, 220), Color(1.f, 1.f, 1.f), _T("プレイヤーの移動速度:%f"), _i_player_data->GetSpeed(_tag));
	}

	if (_arm_tag == "Arm_1")
	{
		SpriteBatch.DrawString(_font, Vector2(0, 240), Color(1.f, 1.f, 1.f), _T("アームの飛ぶ速度:%f"), _i_arm_Data->GetGoSpeed(_arm_tag));
		SpriteBatch.DrawString(_font, Vector2(0, 260), Color(1.f, 1.f, 1.f), _T("アームの戻る速度:%f"), _i_arm_Data->GetReturnSpeed(_arm_tag));
		SpriteBatch.DrawString(_font, Vector2(0, 280), Color(1.f, 1.f, 1.f), _T("アームの最大距離:%d"), _i_arm_Data->GetLimitRange(_arm_tag));
	}

	if (_arm != nullptr)
		_arm->Draw2D();
}

void PlayerBase::Draw3D()
{
	ChangeAnimation();

	_model->SetPosition(_position);
	_model->SetRotation(Vector3(0, _angle - 180, 0));
	
	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetParameter("vp", SceneCamera::Instance().GetCamera()->GetViewProjectionMatrix());

	if (_i_player_data->GetState(_tag) != PlayerEnum::Animation::DAMAGE)
	{
		_shader->SetTechnique("FixModel");
		_model->Draw(/*_shader*/);
	}
	else
	{
		_shader->SetTechnique("DamageModel");
		GraphicsDevice.BeginAlphaBlend();
		_model->Draw(/*_shader*/);
		GraphicsDevice.EndAlphaBlend();
	}
	_i_player_data->SetAngle(_tag, _angle);
	_i_player_data->SetPosition(_tag, _position);

	auto collision_pos = _model->GetPosition();
	collision_pos.y += _model->GetScale().y / 2;
	_hit_box->SetHitBoxPosition(collision_pos);
	//_hit_box->Draw3D();

	if (_arm != nullptr)
		_arm->Draw3D();
}

void PlayerBase::ChangeAnimation()
{
	auto index = _i_player_data->GetState(_tag);

	_animation_count += GameTimer.GetElapsedSecond();

	//! 全てのアニメーショントラックを停止
	for (int i = 0; i < PlayerEnum::Animation::ANIMATION_ALL_TYPE; ++i)
	{
		_model->SetTrackEnable(i, FALSE);
	}

	//! アニメーショントラックと状態が違う場合アニメーショントラックを更新
	if (_animation_index != index)
	{
		_animation_index = index;
		_animation_count = 0;
	}

	//! アニメーショントラックのアニメーションを指定した位置から再生
	_model->SetTrackEnable(_animation_index, TRUE);	
	_model->SetTrackPosition(_animation_index, _animation_count);
}

void PlayerBase::Move(Controller* pad)
{
	auto&& map_data = _i_map_data->GetData();

	//! 移動中か入力受付状態か判定
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

			_index_num.x = (int)Clamp(_index_num.x, 0, map_data[_index_num.z].size() - 1);
		}
		else if (abs_x < abs_z)
		{
			std::signbit(pad->GetPadStateY()) ? _index_num.z-- : _index_num.z++;

			_index_num.z = (int)Clamp(_index_num.z, 0, map_data.size() - 1);
		}

		if (map_data[_index_num.z][_index_num.x] != 'i' &&
			map_data[_index_num.z][_index_num.x] != 'w' &&
			map_data[_index_num.z][_index_num.x] != 'b')
		{
			_new_pos = Vector3_Right * _index_num.x + Vector3_Forward * -_index_num.z;
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
	_arm.reset();
	_arm = nullptr;

	_arm.reset(new Arm(_tag));
	_arm->Initialize();
}

void PlayerBase::DestroyArm()
{
	_arm.reset();
	_arm = nullptr;
}


