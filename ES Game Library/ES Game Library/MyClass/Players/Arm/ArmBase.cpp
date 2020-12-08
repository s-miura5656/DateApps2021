#include "ArmBase.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"
#include "../../Data/MyAlgorithm.h"

ArmBase::ArmBase()
{
	
}

ArmBase::~ArmBase()
{

}

int ArmBase::Update()
{
	auto pad = ControllerManager::Instance().GetController(_player_tag);

	_player_distance = Vector3_Distance(_i_player_data->GetPosition(_player_tag), _position);

	_arm_state = _i_arm_Data->GetState(_tag);

	//! �A�[���̔��ˏ�Ԃ̔���
	if (pad->GetButtonState(GamePad_Button2) && _arm_state == ArmEnum::PunchState::PUNCH)
	{
		_arm_state = ArmEnum::PunchState::PUNCH;
		_i_arm_Data->SetState(_tag, _arm_state);
	}
	else
	{
		_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
		_i_arm_Data->SetState(_tag, _arm_state);
	}

	//! �A�[���𔭎˂��Ă����Ԃ̏���
	if (_arm_state == ArmEnum::PunchState::PUNCH)
	{
		//! �A�[���̍ő勗���̔���
		if (_angle_point.size() >= _i_arm_Data->GetLimitRange(_tag))
		{
			_wait_count++;

			if (_wait_count >= 30)
			{
				_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				_i_arm_Data->SetState(_tag, _arm_state);
				_wait_count = 0;
			}
		}
		else
		{
			MoveArm(pad);
		}

		//! �����蔻��
		HitOtherObject();

		return 0;
	}

	//! �A�[���̖߂��Ԃ̏����̔���
	if (_arm_state == ArmEnum::PunchState::RETURN_PUNCH)
	{
		ArmReturn();
		_shot_effect->Stop(effect_num);

		if (_player_distance < 0.6f)
		{
			_arm_state = ArmEnum::PunchState::NO_PUNCH;
			_i_arm_Data->SetState(_tag, _arm_state);
		}
	}
	
	//! �A�[�����߂��Ă������̏����̔���
	if (_arm_state == ArmEnum::PunchState::NO_PUNCH)
	{
		_i_player_data->SetState(_player_tag, PlayerEnum::Animation::WAIT);
	}

	return 0;
}

void ArmBase::Draw2D()
{
	if (_tag == "Arm_1")
	{
		SpriteBatch.DrawString(_font, Vector2(0, 300), Color(0.f, 0.f, 0.f), _T("AnglePointSize:%d"), _angle_point.size());
		SpriteBatch.DrawString(_font, Vector2(0, 320), Color(0.f, 0.f, 0.f), _T("CreateCount:%d"), ArmBase::_create_count);
		SpriteBatch.DrawString(_font, Vector2(0, 340), Color(0.f, 0.f, 0.f), _T("Pos_X:%f"), _position.x);
		SpriteBatch.DrawString(_font, Vector2(0, 360), Color(0.f, 0.f, 0.f), _T("Pos_Z:%f"), _position.z);
	}
}

void ArmBase::Draw3D()
{
	//! ���f���̍��W�w��ƕ`��
	_model->SetPosition(_position);
	_model->SetRotation(0, _angle - 180, 0);
	_model->Draw();
	_model->SetRotation(0, _angle, 0);

	
	//! �q�b�g�{�b�N�X�̍��W�w��ƕ`��
	auto box_pos = _position;
	box_pos.y += _hit_box->GetModelTag()->GetScale().y;
	auto a = DirectionFromAngle(Vector3(0, _angle, 0));
	_hit_box->SetHitBoxPosition(box_pos + a * 0.3f);
	_hit_box->Draw3D();

	//! �G�t�F�N�g�̍��W�w��ƕ`��
	_shot_effect->SetSpeed(effect_num, 1.0f);
	_shot_effect->SetScale(effect_num, 1.0f);
	_shot_effect->SetRotation(effect_num, Vector3(0, _angle, 0));
	_shot_effect->SetPosition(effect_num, _position + (-a * 0.5f) + (Vector3_Up * 0.5f));
}

//! @fn �A�[���̈ړ�(�Ȃ���)
//! @brief �A�[���̈ړ�����������
//! @param �R���g���[���[
void ArmBase::MoveArm(Controller* pad)
{
	auto&& map_data = _i_map_data->GetData();

	if (TurnArm(pad))
		return;

	//! �ړ����������łȂ�������
	if (_move_flag)
	{
		_position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
		_lerp_count += _i_arm_Data->GetGoSpeed(_tag);

		if (_lerp_count >= 1.f)
		{
			_move_flag  = false;
			_angle_point.push_back(_position);
			_lerp_count = 0;

			//! �p�b�h��|���Ă�����A�[���̌������͏��
			if (pad->GetPadStateX() != Axis_Center || pad->GetPadStateY() != Axis_Center)
			{
				_angle = AngleCalculating(pad->GetPadStateX(), pad->GetPadStateY());
				_angle = AngleClamp(_angle);

				if (_angle != _old_angle)
				{
					_old_angle = _angle;
					_turn_flag = true;
				}
			}
		}
	}
	else
	{
		int old_index_x = _index_num.x;
		int old_index_z = _index_num.z;
		
		Vector3 dir = DirectionFromAngle(Vector3(0, _angle, 0));

		auto abs_x = fabs(dir.x);
		auto abs_z = fabs(dir.z);
		
		//! �����̐�Βl�𔻒肵�Ă���A�傫���ق��̎��̕�������i�ޕ���������
		if (abs_x > abs_z)
		{
			signbit(dir.x) ? _index_num.x-- : _index_num.x++;
			_index_num.x = Clamp(_index_num.x, 0, map_data[_index_num.z].size() - 1);
		}
		else if (abs_x < abs_z)
		{
			signbit(dir.z) ? _index_num.z++ : _index_num.z--;
			_index_num.z = Clamp(_index_num.z, 0, map_data.size() - 1);
		}
		
		//! �ǂ̔���
		if (map_data[_index_num.z][_index_num.x] != 'i' &&
			map_data[_index_num.z][_index_num.x] != 'w')
		{
			_new_pos = Vector3_Right * _index_num.x + Vector3_Forward * -_index_num.z;
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

bool ArmBase::TurnArm(Controller* pad)
{
	//! �t���O�������Ă�����A�[���̌�������
	if (_turn_flag)
	{
		_wait_count++;

		if (_wait_count > 30)
		{
			_wait_count = 0;
			_turn_flag = false;
		}
	}

	return _turn_flag;
}

//! @fn �A�[���̖߂�
//! @brief �A�[���̖߂�ړ�����������
void ArmBase::ArmReturn()
{
	auto angle_point_size = _angle_point.size();

	Vector3 move_dir = Vector3_Normalize(_angle_point[angle_point_size - 1] - _position);

	auto dist = Vector3_Distance(_position, _angle_point[angle_point_size - 1]);

	//! ��苗���܂Œ��p�n�_�ɋ߂Â�����z����폜
	if (dist < 0.3f && angle_point_size > 1)
	{
		_angle_point.erase(_angle_point.begin() + (angle_point_size - 1));
		return;
	}

	move_dir *= _i_arm_Data->GetReturnSpeed(_tag);

	_angle = -AngleCalculating(move_dir.x, move_dir.z);

	_position += move_dir;

	//! �ړ�������������z����폜
	if (move_dir == Vector3_Zero && angle_point_size > 1)
	{
		_angle_point.erase(_angle_point.begin() + (angle_point_size - 1));
	}
}

void ArmBase::HitOtherObject()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		std::string name = PLAYER_TAG + std::to_string(i + 1);

		//! �����̃^�O�������玟��
		if (name == _player_tag)
			continue;

		//! �v���C���[�ɓ���������
		if (_hit_box->IsHitObjectsSquare(name))
		{
			auto&& i_player_data = _i_player_data.get();
			auto&& i_arm_data    = _i_arm_Data.get();
			
			int damege = i_player_data->GetAttackPowor(_player_tag);
			int hitpoint = i_player_data->GetHitPoint(name);
			
			hitpoint -= damege;

			//! �_���[�W�d���ł͂Ȃ��Ƃ���HP�����炷
			if (i_player_data->GetState(name) != PlayerEnum::Animation::DAMAGE)
			{
				i_player_data->SetHitPoint(name, hitpoint);
			}

			if (i_player_data->GetHitPoint(name) <= 0)
			{
				i_player_data->SetKillCount(_player_tag, i_player_data->GetKillCount(_player_tag) + 1);
				_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				i_arm_data->SetState(_tag, _arm_state);
//				i_player_data->SetState(name, PlayerEnum::Animation::DEATH);
			}
			else
			{
				_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				i_arm_data->SetState(_tag, _arm_state);
				i_player_data->SetState(name, PlayerEnum::Animation::DAMAGE);
			}
			
			break;
		}
	}
}
