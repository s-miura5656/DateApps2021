#include "PlayerBase.h"
#include "../Data/MyAlgorithm.h"
#include "../Managers/SceneManager/SceneManager.h"
#include "../ParticleSystem/Particle.h"

#pragma region ��{�@�\
PlayerBase::PlayerBase()
{

}

PlayerBase::~PlayerBase()
{

}

int PlayerBase::Update()
{
	auto pad = InputManager::Instance().GetGamePad(_tag);
	auto&& player_data = _i_player_data;

	ParameterLevel();

	pad->Refresh();

	DebugControll();

	//! ����ł鎞�Ƃ����łȂ��Ƃ��̔���
	if (_death_flag)
	{
		_respawn_time++;

		if (_respawn_time > RESPAWN_TIME)
		{
			player_data->SetHitPoint(_tag, RESPAWN_HITPOINT);
			player_data->SetState(_tag, PlayerEnum::Animation::WAIT);
			_respawn_time = 0;
			_death_flag = false;
			_move_flag  = false;
			_transform.position = IMapData::GetRespawnPosition();
			_index_num.x = 7;
			_index_num.z = 6;
			player_data->SetIndexNum(_tag, _index_num);
			player_data->SetPosition(_tag, _transform.position); 
		}
	}
	else
	{
		if (player_data->GetState(_tag) == PlayerEnum::Animation::DEATH)
		{
			DestroyArm();
			_death_flag      = true;
			player_data->SetInvincibleMode(_tag, true);
			return 0;
		}
		else
		{
			InvincibleMode();
		}
		

		//! �_���[�W��Ԃ̔���
		if (player_data->GetState(_tag) == PlayerEnum::Animation::DAMAGE)
		{
			_damage_hit_count++;

			if (_damage_hit_count > DEATH_RIGOR)
			{
				player_data->SetState(_tag, PlayerEnum::Animation::DEATH);
				_damage_hit_count = 0;
			}

			DestroyArm();

			return 0;
		}
		
		//! �p���`���ˏ�ԂȂ炷�����܃��^�[��
		if (player_data->GetState(_tag) == PlayerEnum::Animation::ATTACK)
		{
			player_data->SetIndexNum(_tag, _index_num);
			
			_arm->Update();

			return 0;
		}
		else if (player_data->GetState(_tag) == PlayerEnum::Animation::SHOT)
		{
			_shot_pending_count++;

			if (_shot_pending_count > player_data->GetShotRigorFrame(_tag))
			{
				player_data->SetState(_tag, PlayerEnum::Animation::ATTACK);
				player_data->SetPosition(_tag, _transform.position);
				_shot_pending_count = 0;
				CreateArm();
			}

			return 0;
		}
		else
		{
			DestroyArm();

			if (!_move_flag)
			{
				//! �v���C���[�ړ�
				if (pad->Stick(STICK_INFO::LEFT_STICK) != STICK_CENTER)
				{
					InputAngle(pad);
					player_data->SetAngle(_tag, _transform.rotation.y);
					player_data->SetState(_tag, PlayerEnum::Animation::MOVE);
				}
				else
				{
					player_data->SetState(_tag, PlayerEnum::Animation::WAIT);
				}

				auto a = pad->Trigger(TRIGGER_INFO::LEFT_TRIGGER);

				//! ���P�b�g�p���`���ː؂�ւ�
				if (pad->Button(BUTTON_INFO::BUTTON_B))
				{
					player_data->SetState(_tag, PlayerEnum::Animation::SHOT);
					player_data->SetPosition(_tag, _transform.position);
				}
			}
		}

		if (player_data->GetState(_tag) == PlayerEnum::Animation::MOVE)
		{
			InputMove(pad);
		}
	}

	SetCollisionPosition();
	return 0;
}

void PlayerBase::Draw2D()
{
	if (_tag == "Player_1")
	{
		//SpriteBatch.DrawString(_font, Vector2(0, 180), Color(1.f, 1.f, 1.f), _T("PL1�̏����|�C���g:%d"), _i_player_data->GetRankingPoint(_tag));
		//SpriteBatch.DrawString(_font, Vector2(0, 280), Color(1.f, 1.f, 1.f), _T("PL1�̃��x��:%d"), _i_player_data->GetParameterLevel(_tag));
		//SpriteBatch.DrawString(_font, Vector2(0, 200), Color(1.f, 1.f, 1.f), _T("�v���C���[��HP:%d"), _i_player_data->GetHitPoint(_tag));
		//SpriteBatch.DrawString(_font, Vector2(0, 220), Color(1.f, 1.f, 1.f), _T("�v���C���[�̈ړ����x:%f"), _i_player_data->GetSpeed(_tag));
		//SpriteBatch.DrawString(_font, Vector2(0, 260), Color(1.f, 1.f, 1.f), _T("�v���C���[�̔��ˍd��:%d"), _i_player_data->GetShotRigorFrame(_tag));

	}
	if (_tag == "Player_2") {
		//SpriteBatch.DrawString(_font, Vector2(0, 300), Color(1.f, 1.f, 1.f), _T("PL2�̃��x��:%d"), _i_player_data->GetParameterLevel(_tag));
		//SpriteBatch.DrawString(_font, Vector2(0, 200), Color(1.f, 1.f, 1.f), _T("PL2�̏����|�C���g:%d"), _i_player_data->GetRankingPoint(_tag));
	}

	if (_tag == "Player_3") {
		//SpriteBatch.DrawString(_font, Vector2(0, 320), Color(1.f, 1.f, 1.f), _T("PL3�̃��x��:%d"), _i_player_data->GetParameterLevel(_tag));
		//SpriteBatch.DrawString(_font, Vector2(0, 220), Color(1.f, 1.f, 1.f), _T("PL3�̏����|�C���g:%d"), _i_player_data->GetRankingPoint(_tag));
	}
if (_tag == "Player_4") { 
	//SpriteBatch.DrawString(_font, Vector2(0, 340), Color(1.f, 1.f, 1.f), _T("PL4�̃��x��:%d"), _i_player_data->GetParameterLevel(_tag));
	//SpriteBatch.DrawString(_font, Vector2(0, 240), Color(1.f, 1.f, 1.f), _T("PL4�̏����|�C���g:%d"), _i_player_data->GetRankingPoint(_tag));
    }
	if (_arm_tag == "Arm_1")
	{
		//SpriteBatch.DrawString(_font, Vector2(0, 320), Color(1.f, 1.f, 1.f), _T("�A�[���̐i�ޑ��x:%f"), _i_arm_Data->GetGoSpeed(_arm_tag));
		//SpriteBatch.DrawString(_font, Vector2(0, 380), Color(1.f, 1.f, 1.f), _T("�A�[���̍ő勗��:%d"), _i_arm_Data->GetLimitRange(_arm_tag));
		//SpriteBatch.DrawString(_font, Vector2(0, 440), Color(1.f, 1.f, 1.f), _T("�A�[���̉�]�d��:%d"), _i_arm_Data->GetTurnFrame(_arm_tag));
	}

	if (_arm != nullptr)
		_arm->Draw2D();
}

void PlayerBase::Draw3D()
{
	//! ����ł鎞�Ƃ����łȂ��Ƃ��̔���
	if (_death_flag)
	{
		_destroy_effect->SetPosition(_transform.position + Vector3_Up);
		_destroy_effect->PlayOneShot();
	}
	else
	{

		_destroy_effect->Stop();
		
		ChangeAnimation();

		DrawModel();
		
		_hit_box->SetModelPosition();
		_hit_box->SetModelScale();
		
//		_hit_box->Draw3D();
		
		if (_arm != nullptr)
		{
			_arm->Draw3D();
		}
	}
}

void PlayerBase::DrawAlpha3D()
{
}
#pragma endregion

#pragma region �`��֌W
//! @fn �v���C���[���f���̕`��
void PlayerBase::DrawModel()
{
	//! ���f���̃p�����[�^�[���Z�b�g
	_model->SetPosition(_transform.position);
	_model->SetRotation(Vector3(-15, _transform.rotation.y, 0));
	_model->SetMaterial(_model_material);

	//! �V�F�[�_�[���ɒl���Z�b�g
	auto camera = SceneCamera::Instance().GetCamera();
	_shader->SetParameter("model_ambient", _model_material.Ambient);
	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetParameter("eye_pos", camera.GetPosition());

	Matrix vp = camera->GetViewProjectionMatrix();
	_shader->SetParameter("vp", vp);

	if (_i_player_data->GetState(_tag) != PlayerEnum::Animation::DAMAGE)
	{
		_shader->SetTechnique("FixAnimationModel");
		_model->Draw(_shader);
	}
	else
	{
		_shader->SetTechnique("DamageAnimationModel");
		GraphicsDevice.BeginAlphaBlend();
		_model->Draw(_shader);
		GraphicsDevice.EndAlphaBlend();
	}

	_model->SetRotation(_transform.rotation);

	_i_player_data->SetAngle(_tag, _transform.rotation.y);
	_i_player_data->SetPosition(_tag, _transform.position);
}

//! @fn �v���C���[���f���̃A�j���[�V�����؂�ւ�
void PlayerBase::ChangeAnimation()
{
	auto index = _i_player_data->GetState(_tag);

	_animation_count += GameTimer.GetElapsedSecond();

	//! �S�ẴA�j���[�V�����g���b�N���~
	for (int i = 0; i < PlayerEnum::Animation::ANIMATION_ALL_TYPE; ++i)
	{
		_model->SetTrackEnable(i, FALSE);
	}

	//! �A�j���[�V�����g���b�N�Ə�Ԃ��Ⴄ�ꍇ�A�j���[�V�����g���b�N���X�V
	if (_animation_index != index)
	{
		_animation_index = index;
		_animation_count = 0;
	}

	//! �A�j���[�V�����g���b�N�̃A�j���[�V�������w�肵���ʒu����Đ�
	_model->SetTrackEnable(_animation_index, TRUE);	

	if (_animation_index == PlayerEnum::Animation::SHOT)
	{
		float shot_frame = 60.f / (float)_i_player_data->GetShotRigorFrame(_tag);
		_model->SetTrackPosition(_animation_index, _animation_count * shot_frame);
	}
	else if (_animation_index == PlayerEnum::Animation::MOVE)
	{
		_model->SetTrackPosition(_animation_index, _animation_count);
	}
	else
	{
		_model->SetTrackPosition(_animation_index, _animation_count);
	}
}
#pragma endregion

#pragma region ����֌W
//! @fn �ړ�����
void PlayerBase::InputMove(BaseInput* pad)
{
	InputMoveDirection(pad);
	Move();
}

void PlayerBase::Move()
{
	if (!_move_flag)
		return;

	auto&& player_data = _i_player_data;

	_transform.position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
	_lerp_count += player_data->GetSpeed(_tag);
	_lerp_count = Clamp(_lerp_count, 0, 1);

	if (_lerp_count >= _moving_completion_end_value)
	{
		_move_flag  = false;
		_lerp_count = 0;
		player_data->SetPosition(_tag, _transform.position);
	}
}

void PlayerBase::InputMoveDirection(BaseInput* pad)
{
	if (_move_flag)
		return;

	auto&& map_data = _i_map_data->GetData();
	auto&& player_data = _i_player_data;

	auto pad_x = pad->Stick(STICK_INFO::LEFT_STICK).x;
	auto pad_y = pad->Stick(STICK_INFO::LEFT_STICK).y;

	float abs_x = fabsf(pad_x);
	float abs_z = fabsf(pad_y);

	int old_index_x = _index_num.x;
	int old_index_z = _index_num.z;

	if (abs_x > abs_z) 
	{
		std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).x) ? _index_num.x-- : _index_num.x++;
		_index_num.x = (int)Clamp(_index_num.x, 0, map_data[_index_num.z].size() - 1);
	}
	else if (abs_x < abs_z) 
	{
		std::signbit(pad->Stick(STICK_INFO::LEFT_STICK).y) ? _index_num.z++ : _index_num.z--;
		_index_num.z = (int)Clamp(_index_num.z, 0, map_data.size() - 1);
	}

	if (map_data[_index_num.z][_index_num.x] != 'i' &&
		map_data[_index_num.z][_index_num.x] != 'w' &&
		map_data[_index_num.z][_index_num.x] != 'b' &&
		map_data[_index_num.z][_index_num.x] != 'd' &&
		map_data[_index_num.z][_index_num.x] != 's')
	{
		_new_pos = Vector3_Right * _index_num.x + Vector3_Forward * -_index_num.z;
		player_data->SetIndexNum(_tag, _index_num);
		_move_flag = true;
	}
	else
	{
		_index_num.x = old_index_x;
		_index_num.z = old_index_z;
	}

	_old_pos = _transform.position;
}

//! @fn �����̓���
void PlayerBase::InputAngle(BaseInput* pad)
{
	_transform.rotation.y = AngleCalculating(pad->Stick(STICK_INFO::LEFT_STICK).x, pad->Stick(STICK_INFO::LEFT_STICK).y);
	_transform.rotation.y = AngleClamp(_transform.rotation.y);

	if (_transform.rotation.y != _old_angle)
	{
		_old_angle = _transform.rotation.y;
	}
}
#pragma endregion

#pragma region �����蔻��
//! @fn �����蔻��̍��W�ݒ�
void PlayerBase::SetCollisionPosition()
{
	auto collision_pos = _transform.position;
	collision_pos.y += _model->GetScale().y / 2;
	_hit_box->SetHitBoxPosition(collision_pos);
}
#pragma endregion

#pragma region Arm�֘A
//! fn �A�[���̐���
void PlayerBase::CreateArm()
{
	_arm.reset();
	_arm = nullptr;

	_arm.reset(new Arm(_tag));
	_arm->Initialize();
}

//! @fn �A�[���̔j��
void PlayerBase::DestroyArm()
{
	_arm.reset();
	_arm = nullptr;
}
#pragma endregion

#pragma region �f�o�b�O�֌W
//! @fn �f�o�b�O�p�p�����[�^�[����
void PlayerBase::DebugControll()
{
	KeyboardBuffer keybuffer = Keyboard->GetBuffer();
	KeyboardState keystate   = Keyboard->GetState();


	//! �A�[���̔�ԑ��x����
	float speed = _i_arm_Data->GetGoSpeed(_arm_tag);

	if (keybuffer.IsPressed(Keys_Up) && keystate.IsKeyDown(Keys_LeftControl))
		speed += 0.01f;

	if (keybuffer.IsPressed(Keys_Down) && keystate.IsKeyDown(Keys_LeftControl))
		speed -= 0.01f;

	speed = Clamp(speed, 0.01f, 10.0f);
	_i_arm_Data->SetGoSpeed(_arm_tag, speed);


	//! �A�[���̖߂鑬�x����
	speed = _i_arm_Data->GetReturnSpeed(_arm_tag);

	if (keybuffer.IsPressed(Keys_Up) && keystate.IsKeyDown(Keys_LeftAlt))
		speed += 0.01f;

	if (keybuffer.IsPressed(Keys_Down) && keystate.IsKeyDown(Keys_LeftAlt))
		speed -= 0.01f;

	speed = Clamp(speed, 0.01f, 10.0f);
	_i_arm_Data->SetReturnSpeed(_arm_tag, speed);


	//! �v���C���[�̈ړ����x����
	speed = _i_player_data->GetSpeed(_tag);

	if (keybuffer.IsPressed(Keys_Up) && keystate.IsKeyDown(Keys_LeftShift))
		speed += 0.01f;

	if (keybuffer.IsPressed(Keys_Down) && keystate.IsKeyDown(Keys_LeftShift))
		speed -= 0.01f;

	speed = Clamp(speed, 0.01f, 10.0f);
	_i_player_data->SetSpeed(_tag, speed);


	//! �A�[���̌��E����
	int range = _i_arm_Data->GetLimitRange(_arm_tag);

	if (keybuffer.IsPressed(Keys_Right))
		range++;

	if (keybuffer.IsPressed(Keys_Left))
		range--;

	range = (int)Clamp(range, 1, 20);

	_i_arm_Data->SetLimitRange(_arm_tag, range);
}
void PlayerBase::ParameterLevel()
{
	int old_count = _i_player_data->GetParameterLevel(_tag);
	_new_point = _i_player_data->GetRankingPoint(_tag);
	if (_new_point != _old_point)
	{
		if (_new_point < 500)
		{
			_i_player_data->SetParameterLevel(_tag, 1);
		}
		else if (_new_point >= 500 && _new_point < 1000)
		{
			_i_player_data->SetParameterLevel(_tag, 2);
		}
		else if (_new_point >= 1000 && _new_point < 1500)
		{
			_i_player_data->SetParameterLevel(_tag, 3);
		}
		else if (_new_point >= 1500)
		{
			_i_player_data->SetParameterLevel(_tag, 4);
		}
		_old_point = _new_point;
	}

	if (old_count == _new_point)
		return;

	switch (_i_player_data->GetParameterLevel(_tag))
	{
	case 1:
		_i_player_data->SetShotRigorFrame(_tag, 30);
		_i_player_data->SetSpeed(_tag, 0.05f);
		_i_arm_Data->SetLimitRange(_arm_tag, 10);
		_i_arm_Data->SetGoSpeed(_arm_tag, 0.1f);
		break;
	case 2:
		_i_player_data->SetShotRigorFrame(_tag, 25);
		_i_player_data->SetSpeed(_tag, 0.06f);
		_i_arm_Data->SetLimitRange(_arm_tag, 12);
		_i_arm_Data->SetGoSpeed(_arm_tag, 0.125f);
		break;
	case 3:
		_i_player_data->SetShotRigorFrame(_tag, 20);
		_i_player_data->SetSpeed(_tag, 0.07f);
		_i_arm_Data->SetLimitRange(_arm_tag, 14);
		_i_arm_Data->SetGoSpeed(_arm_tag, 0.15f);
		break;
	case 4:
		_i_player_data->SetShotRigorFrame(_tag, 15);
		_i_player_data->SetSpeed(_tag, 0.08f);
		_i_arm_Data->SetLimitRange(_arm_tag, 16);
		_i_arm_Data->SetGoSpeed(_arm_tag, 0.2f);
		break;
	}
}

void PlayerBase::InvincibleMode()
{
	if (!_i_player_data->GetInvincibleMode(_tag))
		return;

	_invincible_count++;

	if (_invincible_count >= INVINCIBLE_FRAME)
	{
		_invincible_count = 0;
		_i_player_data->SetInvincibleMode(_tag, false);
	}
	
}
