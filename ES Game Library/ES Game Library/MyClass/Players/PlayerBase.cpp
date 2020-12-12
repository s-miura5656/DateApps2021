#include "PlayerBase.h"
#include "../Data/MyAlgorithm.h"
#include "../Managers/SceneManager/SceneManager.h"

PlayerBase::PlayerBase()
{

}

PlayerBase::~PlayerBase()
{

}

int PlayerBase::Update()
{
	auto pad = ControllerManager::Instance().GetController(_tag);
	pad->GamePadRefresh();

	DebugControll();

	//! ����ł鎞�Ƃ����łȂ��Ƃ��̔���
	if (_death_flag)
	{
		_respawn_time++;

		if (_respawn_time > 120)
		{
			_i_player_data->SetHitPoint(_tag, 1000);
			_i_player_data->SetState(_tag, PlayerEnum::Animation::WAIT);
			_respawn_time = 0;
			_death_flag = false;
			_move_flag = false;
			_position = _new_pos;
		}
	}
	else
	{
		if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::DEATH)
		{
			_death_flag = true;
			DestroyArm();
			return 0;
		}

		//! �_���[�W��Ԃ̔���
		if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::DAMAGE)
		{
			_damage_count++;

			if (_damage_count > 30)
			{
				_i_player_data->SetState(_tag, PlayerEnum::Animation::DEATH);
				_damage_count = 0;
			}

			DestroyArm();

			return 0;
		}

		//! �ړ������ҋ@��������
		if (!_move_flag)
		{
			//! �p���`���ˏ�ԂȂ炷�����܃��^�[��
			if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::ATTACK)
			{
				_i_player_data->SetIndexNum(_tag, _index_num);
				_arm->Update();
				return 0;
			}
			else if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::SHOT)
			{
				_shot_pending_count++;

				if (_shot_pending_count > 60)
				{
					_i_player_data->SetState(_tag, PlayerEnum::Animation::ATTACK);
					_i_player_data->SetPosition(_tag, _position);
					_shot_pending_count = 0;
					CreateArm();
				}

				return 0;
			}
			else
			{
				DestroyArm();

				//! �v���C���[�ړ�
				if (pad->GetPadStateX() != Axis_Center || pad->GetPadStateY() != Axis_Center)
				{
					_angle = AngleCalculating(pad->GetPadStateX(), pad->GetPadStateY());
					_angle = AngleClamp(_angle);
					_i_player_data->SetState(_tag, PlayerEnum::Animation::MOVE);
				}
				else
				{
					_i_player_data->SetState(_tag, PlayerEnum::Animation::WAIT);
				}

				//! ���P�b�g�p���`���ː؂�ւ�
				if (pad->GetButtonState(GamePad_Button2))
				{
					_i_player_data->SetState(_tag, PlayerEnum::Animation::SHOT);
					_i_player_data->SetPosition(_tag, _position);
				}
			}
		}

		if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::MOVE)
		{
			//! �ړ�
			Move(pad);
		}
	}

	SetCollisionPosition();

	return 0;
}

void PlayerBase::Draw2D()
{
	if (_tag == "Player_1")
	{
//		SpriteBatch.DrawString(_font, Vector2(0, 180), Color(1.f, 1.f, 1.f), _T("�v���C���[�̏����|�C���g:%d"), _i_player_data->GetRankingPoint(_tag));
//		SpriteBatch.DrawString(_font, Vector2(0, 200), Color(1.f, 1.f, 1.f), _T("�v���C���[��HP:%d"), _i_player_data->GetHitPoint(_tag));
//		SpriteBatch.DrawString(_font, Vector2(0, 220), Color(1.f, 1.f, 1.f), _T("�v���C���[�̈ړ����x:%f"), _i_player_data->GetSpeed(_tag));
	}

	if (_arm_tag == "Arm_1")
	{
//		SpriteBatch.DrawString(_font, Vector2(0, 240), Color(1.f, 1.f, 1.f), _T("�A�[���̔�ԑ��x:%f"), _i_arm_Data->GetGoSpeed(_arm_tag));
//		SpriteBatch.DrawString(_font, Vector2(0, 260), Color(1.f, 1.f, 1.f), _T("�A�[���̖߂鑬�x:%f"), _i_arm_Data->GetReturnSpeed(_arm_tag));
//		SpriteBatch.DrawString(_font, Vector2(0, 280), Color(1.f, 1.f, 1.f), _T("�A�[���̍ő勗��:%d"), _i_arm_Data->GetLimitRange(_arm_tag));
	}

	if (_arm != nullptr)
		_arm->Draw2D();
}

void PlayerBase::Draw3D()
{
	//! ����ł鎞�Ƃ����łȂ��Ƃ��̔���
	if (_death_flag)
	{
		if (_handle == INT_MAX)
		{
			_handle = _destroy_effect->Play(_position + Vector3_Up);
		}
	}
	else
	{
		_destroy_effect->Stop(_handle);
		_handle = INT_MAX;

		ChangeAnimation();

		DrawModel();
		
		_hit_box->SetModelPosition();
		_hit_box->SetModelScale();
//		_hit_box->Draw3D();
		
		if (_arm != nullptr)
		{
			_arm->Draw3D();

			DrawWireModel();
		}
	}
}

void PlayerBase::DrawAlpha3D()
{
}

//! @fn �v���C���[���f���̕`��
void PlayerBase::DrawModel()
{
	//! ���f���̃p�����[�^�[���Z�b�g
	_model->SetPosition(_position);
	_model->SetRotation(Vector3(0, _angle - 180, 0));
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
		_shader->SetTechnique("FixModel");
		_model->Draw(_shader);
	}
	else
	{
		_shader->SetTechnique("DamageModel");
		GraphicsDevice.BeginAlphaBlend();
		_model->Draw(_shader);
		GraphicsDevice.EndAlphaBlend();
	}

	_model->SetRotation(Vector3(0, _angle, 0));

	_i_player_data->SetAngle(_tag, _angle);
	_i_player_data->SetPosition(_tag, _position);
}

//! @fn ���C���[���f���̕`��
void PlayerBase::DrawWireModel()
{
	auto camera = SceneCamera::Instance().GetCamera();

	_wire_shader->SetTexture("m_Texture", *_wire_texture);
	_wire_shader->SetParameter("model_ambient", _model_material.Ambient);
	_wire_shader->SetParameter("eye_pos", camera.GetPosition());
	
	Matrix vp = camera->GetViewProjectionMatrix();

	for (auto&& model : _wire_models)
	{
		model->SetMaterial(_model_material);
	}

	auto arm_positions = _i_arm_Data->GetAnglePositions(_arm_tag);
	auto arm_angles    = _i_arm_Data->GetAngles(_arm_tag);

	for (int i = 0; i < arm_positions.size(); ++i)
	{
		_wire_models[i]->SetPosition(arm_positions[i]);
		_wire_models[i]->SetRotation(Vector3(0, arm_angles[i] + 180, 0));
		Matrix world = _wire_models[i]->GetWorldMatrix();
		_wire_shader->SetParameter("wvp", world * vp);
		_wire_models[i]->Draw(_wire_shader);
	}
}

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
	_model->SetTrackPosition(_animation_index, _animation_count);
}

void PlayerBase::Move(Controller* pad)
{
	auto&& map_data = _i_map_data->GetData();

	//! �ړ��������͎�t��Ԃ�����
	if (_move_flag)
	{
		_position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
		_lerp_count += _i_player_data->GetSpeed(_tag);

		_lerp_count = Clamp(_lerp_count, 0, 1);

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

//! �����蔻��̍��W�ݒ�
void PlayerBase::SetCollisionPosition()
{
	auto collision_pos = _position;
	collision_pos.y += _model->GetScale().y / 2;
	_hit_box->SetHitBoxPosition(collision_pos);
}

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

void PlayerBase::DebugControll()
{
	KeyboardBuffer keybuffer = Keyboard->GetBuffer();
	KeyboardState keystate = Keyboard->GetState();


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
