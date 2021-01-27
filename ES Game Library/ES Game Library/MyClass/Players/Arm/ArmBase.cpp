#include "ArmBase.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include "../../ParticleSystem/Particle.h"
#include "../../Item/ItemCounter/ItemCounter.h"

ArmBase::ArmBase()
{
	
}

ArmBase::~ArmBase()
{

}

int ArmBase::Update()
{
	auto pad = InputManager::Instance().GetGamePad(_player_tag);

	_player_distance = Vector3_Distance(_i_player_data->GetPosition(_player_tag), _transform.position);

	_arm_state = _i_arm_Data->GetState(_tag);

	_i_arm_Data->SetAnglePositions(_tag, _angle_positions);

	if (_scale < 2) 
	{
		_scale += 2.0f / 10.0f;
	}

	//! アームの発射状態の判定
	if (pad->Button(BUTTON_INFO::BUTTON_B) && _arm_state == ArmEnum::PunchState::PUNCH)
	{
		//_arm_state = ArmEnum::PunchState::PUNCH;
		//_i_arm_Data->SetState(_tag, _arm_state);
	}
	if(pad->ButtonDown(BUTTON_INFO::BUTTON_B) && _arm_state == ArmEnum::PunchState::PUNCH)
	{
		_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
		_i_arm_Data->SetState(_tag, _arm_state);
	}

	//! アームを発射している状態の処理
	if (_arm_state == ArmEnum::PunchState::PUNCH)
	{
		//! アームの最大距離の判定
		if (_angle_positions.size() >= _i_arm_Data->GetLimitRange(_tag) && _i_player_data->GetStatusTag(_player_tag) != ITEM_ARM_SPEEDUP)
		{
			_wait_count++;

			if (_wait_count >= ARM_MAX_DISTANCE_RIGOR)
			{
				_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				_i_arm_Data->SetState(_tag, _arm_state);
				_wait_count = 0;
			}
		}
		else
		{
			MoveArm(pad);
			SetCollisionPosition(0.2f);
		}

		//! 当たり判定
		HitOtherObject();
		Vector3 back_position = DirectionFromAngle(_transform.rotation) * -0.2f;
		_shot_effect->SetPosition(_transform.position + back_position);

		return 0;
	}

	//! アームの戻り状態の処理の判定
	if (_arm_state == ArmEnum::PunchState::RETURN_PUNCH)
	{
		ArmReturn();
		_shot_effect->Stop();

		if (_player_distance < 0.6f)
		{
			_arm_state = ArmEnum::PunchState::NO_PUNCH;
			_i_arm_Data->SetState(_tag, _arm_state);
		}
	}
	
	//! アームが戻ってきた時の処理の判定
	if (_arm_state == ArmEnum::PunchState::NO_PUNCH)
	{
		_i_player_data->SetState(_player_tag, PlayerEnum::Animation::WAIT);
	}

	return 0;
}

void ArmBase::Draw2D()
{
	auto pad = InputManager::Instance().GetGamePad(_player_tag);

	if (_tag == "Arm_1")
	{
		//SpriteBatch.DrawString(_font, Vector2(0, 300), Color(1.f, 1.f, 1.f), _T("X:%f"), pad->Stick(STICK_INFO::LEFT_STICK).x);
		//SpriteBatch.DrawString(_font, Vector2(0, 320), Color(1.f, 1.f, 1.f), _T("Y:%f"), pad->Stick(STICK_INFO::LEFT_STICK).y);
	}
//	auto scale = _hit_box->GetModelTag()->GetScale();
//	SpriteBatch.DrawString(_font, Vector2(0, 380), Color(255.f, 0.f, 0.f), _T("Scale:%0.1f, %0.1f, %0.1f"), scale.x, scale.y, scale.z);
}

void ArmBase::Draw3D()
{
	//! モデルの座標を
	_model->SetPosition(_transform.position);
	_model->SetScale(_scale);

	if (_arm_state == ArmEnum::PunchState::RETURN_PUNCH)
		_model->SetRotation(0, _transform.rotation.y + 180, 0);
	else
		_model->SetRotation(0, _transform.rotation.y, 0);

	_model->SetMaterial(_model_material);

	//! シェーダーにパラメーターを送る
	auto camera = SceneCamera::Instance().GetCamera();

	Matrix world = _model->GetWorldMatrix();
	_shader->SetParameter("wvp", world * camera->GetViewProjectionMatrix());
	_shader->SetParameter("eye_pos", camera.GetPosition());
	_shader->SetParameter("model_ambient", _model_material.Ambient);
	_shader->SetTexture("m_Texture", *_texture);
	_shader->SetTechnique("FixModel_S1");

	_model->Draw(_shader);
	_model->SetRotation(0, _transform.rotation.y, 0);

	//! ヒットボックスの座標指定と描画
	_hit_box->SetModelPosition();
	_hit_box->SetModelScale();
	//_hit_box->Draw3D();

	//! エフェクトの座標指定と描画
	Vector3 rotation = _transform.rotation;
	rotation.y += 180;
	_shot_effect->SetRotation(rotation);
	_shot_effect->SetScale(8.0 - (0.8f * (_wires.size() + 1)));
	if (_i_player_data->GetStatusTag(_player_tag) == ITEM_ARM_SPEEDUP)
		_shot_effect->SetScale(12.0f);
	_shot_effect->Draw();

	auto limitrange = (int)_i_arm_Data->GetLimitRange(_tag) / 3;

	for (int i = 0; i < _wires.size(); i++)
	{
		if (_wires.size() > limitrange * 2)
		{
			_wires[i]->SetColor(Color(255, 0, 0));
			_wires[i]->SetScale(0.5f);
		}
		else if (_wires.size() > limitrange)
		{
			_wires[i]->SetColor(Color(255, 255, 0));
			_wires[i]->SetScale(1.0f);
		}
		else
		{
			_wires[i]->SetColor(Color(0, 255, 0));
			_wires[i]->SetScale(1.5f);
		}
	}
	//! ワイヤーモデルの描画
	for (auto& wire : _wires)
	{
		if (_i_player_data->GetStatusTag(_player_tag) == ITEM_ARM_SPEEDUP)
		{
			if (Rainbow_wire >= 3)
			{
				Rainbow_wire = 0;
			}
			switch (Rainbow_wire)
			{
			case 0:
				for (int i = 0; i < _wires.size(); i++)
					_wires[i]->SetColor(Color(255, 0, 0));
				break;
			case 1:
				for (int i = 0; i < _wires.size(); i++)
					_wires[i]->SetColor(Color(0, 255, 0));
				break;
			case 2:
				for (int i = 0; i < _wires.size(); i++)
					_wires[i]->SetColor(Color(0, 0, 255));
				break;
			}
			Rainbow_wire++;
			wire->SetScale(1.5f);
		}
		wire->Draw3D();
	}
}

//! @fn アームの移動(曲がる)
//! @brief アームの移動を処理する
//! @param コントローラー
void ArmBase::MoveArm(BaseInput* pad)
{
	if (TurnArm())
		return;

	InputMoveDirection(pad);
	Move(pad);
}

void ArmBase::Move(BaseInput* pad)
{
	if (!_move_flag)
		return;

	_transform.position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
	_lerp_count += _i_arm_Data->GetGoSpeed(_tag);
	_shot_effect->PlayOneShot();

	if (_lerp_count >= 1.f)
	{
		_move_flag = false;
		_lerp_count = 0;
		ChangeDirection(pad);
		CreateWire();
		_angle_positions.push_back(_transform.position);
		_i_arm_Data->SetPosition(_tag, _transform.position);
	}
}

void ArmBase::InputMoveDirection(BaseInput* pad)
{
	if (_move_flag)
		return;

	auto&& map_data = _i_map_data->GetData();

	int old_index_x = _index_num.x;
	int old_index_z = _index_num.z;

	Vector3 dir = DirectionFromAngle(Vector3(0, _transform.rotation.y, 0));

	auto abs_x = fabs(dir.x);
	auto abs_z = fabs(dir.z);

	//! 方向の絶対値を判定してから、大きいほうの軸の符号から進む方向を決定
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

	//! 壁の判定
	if (map_data[_index_num.z][_index_num.x] != 'i' &&
		map_data[_index_num.z][_index_num.x] != 'w')
	{
		_new_pos = Vector3_Right * _index_num.x + Vector3_Forward * -_index_num.z + Vector3_Up * offset_y;
		_move_flag = true;
	}
	else if (map_data[_index_num.z][_index_num.x] == 'i' ||
			 map_data[_index_num.z][_index_num.x] == 'w')
	{
		_index_num.x = old_index_x;
		_index_num.z = old_index_z;
		_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
		_i_arm_Data->SetState(_tag, _arm_state);
		Vector3 front_position = DirectionFromAngle(_transform.rotation) * 0.7f;
		_wall_hit_effect->SetPosition(_transform.position + front_position);
		_wall_hit_effect->PlayOneShot();
	}
	else
	{
		_index_num.x = old_index_x;
		_index_num.z = old_index_z;
	}

	_old_pos = _transform.position;
}

bool ArmBase::TurnArm()
{
	//! フラグがたっていたらアームの向き入力
	if (_turn_flag)
	{
		_wait_count++;
		_transform.rotation.y = _new_angle;
		SetCollisionPosition(0.0f);

		if (_wait_count > _i_arm_Data->GetTurnFrame(_tag))
		{
			_old_angle = _transform.rotation.y;
			_wait_count = 0;
			_turn_count = 0;
			_turn_flag  = false;
		}
	}

	return _turn_flag;
}

//! @fn アームの戻り
//! @brief アームの戻り移動を処理する
void ArmBase::ArmReturn()
{
	auto angle_point_size = _angle_positions.size();

	Vector3 move_dir = Vector3_Normalize(_angle_positions[angle_point_size - 1] - _transform.position);

	auto dist = Vector3_Distance(_transform.position, _angle_positions[angle_point_size - 1]);

	//! 一定距離まで中継地点に近づいたら配列を削除
	if (dist < 0.3f && angle_point_size > 1)
	{
		_angle_positions.erase(_angle_positions.begin() + (angle_point_size - 1));
		DeleteWire();
		return;
	}

	move_dir *= _i_arm_Data->GetReturnSpeed(_tag);

	_transform.rotation.y = AngleCalculating(move_dir.x, move_dir.z);

	_transform.position += move_dir;

	//! 移動が完了したら配列を削除
	if (move_dir == Vector3_Zero && angle_point_size > 1)
	{
		_angle_positions.erase(_angle_positions.begin() + (angle_point_size - 1));
		_i_arm_Data->SetAnglePositions(_tag, _angle_positions);
	}
}

//! @fn アームの当たり判定
//! @brief アームが他の当たり判定と当たった時に判定する
void ArmBase::HitOtherObject()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		std::string tag = PLAYER_TAG + std::to_string(i + 1);

		//! 自分のタグだったら次へ
		if (tag == _player_tag)
			continue;

		//! プレイヤーに当たったら
		if (_hit_box->IsHitObjectsSquare(tag))
		{
			auto&& i_player_data = _i_player_data.get();
			auto&& i_arm_data    = _i_arm_Data.get();
			
			if (i_player_data->GetInvincibleMode(tag))
				return;

			int damege = i_player_data->GetAttackPowor(_player_tag);
			int hitpoint = i_player_data->GetHitPoint(tag);
			
			hitpoint -= damege;

			//! ダメージ硬直ではないときにHPを減らす
			if (i_player_data->GetState(tag) != PlayerEnum::Animation::DAMAGE)
			{
				i_player_data->SetHitPoint(tag, hitpoint);
				auto screen_pos = GraphicsDevice.WorldToScreen(_transform.position);
				screen_pos.z = SpriteBatch_TopMost;
				i_arm_data->SetHitPosition(_tag, screen_pos);
			}

			if (i_player_data->GetState(tag) == PlayerEnum::Animation::DEATH)
				break;

			if (i_player_data->GetHitPoint(tag) <= 0)
			{
				i_player_data->SetKillCount(_player_tag, i_player_data->GetKillCount(_player_tag) + 1);
				i_player_data->SetLostPoint(_player_tag, PointCalculation(tag));
				_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				i_arm_data->SetState(_tag, _arm_state);
				i_player_data->SetState(tag, PlayerEnum::Animation::DAMAGE);
			}
			else
			{
				_arm_state = ArmEnum::PunchState::RETURN_PUNCH;
				i_arm_data->SetState(_tag, _arm_state);
				i_player_data->SetState(tag, PlayerEnum::Animation::DAMAGE);
			}
			
			break;
		}
	}
}

//! @fn 当たり判定の座標設定
//! @brief 当たり判定の座標を設定する
void ArmBase::SetCollisionPosition(float front_position)
{
	auto box_pos = _transform.position;
	auto dir = DirectionFromAngle(Vector3(0, _transform.rotation.y, 0));
	_hit_box->SetHitBoxPosition(box_pos + dir * front_position);
}

//! @fn アームの向きを変更
//! @brief パッドの向きからアームの向きを変更
void ArmBase::ChangeDirection(BaseInput* pad)
{
	//! パッドを倒していたらアームの向き入力状態
	if (pad->Stick(STICK_INFO::LEFT_STICK) != STICK_CENTER)
	{
		float axis_x = pad->Stick(STICK_INFO::LEFT_STICK).x;
		float axis_z = pad->Stick(STICK_INFO::LEFT_STICK).y;

		float angle = AngleCalculating(axis_x, axis_z);
		angle = AngleClamp(angle);

		auto&& map_data = _i_map_data->GetData();

		int old_index_x = _index_num.x;
		int old_index_z = _index_num.z;

		Vector3 dir = DirectionFromAngle(Vector3(0, angle, 0));

		auto abs_x = fabs(dir.x);
		auto abs_z = fabs(dir.z);

		//! 方向の絶対値を判定してから、大きいほうの軸の符号から進む方向を決定
		if (abs_x > abs_z)
		{
			signbit(dir.x) ? old_index_x-- : old_index_x++;
			old_index_x = Clamp(old_index_x, 0, map_data[old_index_z].size() - 1);
		}
		else if (abs_x < abs_z)
		{
			signbit(dir.z) ? old_index_z++ : old_index_z--;
			old_index_z = Clamp(old_index_z, 0, map_data.size() - 1);
		}

		//! 壁の判定
		if (map_data[old_index_z][old_index_x] != 'i' &&
			map_data[old_index_z][old_index_x] != 'w')
		{
			//! 向きが変わっていたら向きを更新
			if (angle != _old_angle)
			{
				_shot_effect->Stop();
				_new_angle = angle;
				_turn_flag = true;
			}
		}
	}
}

void ArmBase::CreateWire()
{
	if (_i_player_data->GetStatusTag(_player_tag) == ITEM_ARM_SPEEDUP)
	{
		Transform transform = _transform;
		transform.rotation.y = _new_angle;
		_wires.push_back(std::make_unique<Wire>(transform));
		_wires.rbegin()->get()->Initialize();
	}
	else if (_angle_positions.size() < _i_arm_Data->GetLimitRange(_tag) - 1)
	{
		Transform transform = _transform;
		transform.rotation.y = _new_angle;
		_wires.push_back(std::make_unique<Wire>(transform));
		_wires.rbegin()->get()->Initialize();
	}
}

void ArmBase::DeleteWire()
{
	if (!_wires.empty())
	{
		_wires.rbegin()->reset();
		_wires.erase(_wires.begin() + (_wires.size() - 1));
	}
}

int ArmBase::PointCalculation(std::string other_player_tag)
{
	auto player_data = _i_player_data.get();

	int point = 300;
	if (player_data->GetRankingPoint(other_player_tag) < point)
	{
		point = player_data->GetRankingPoint(other_player_tag);
		player_data->SetRankingPoint(other_player_tag, 0);
	}
	else
	{
		//point = LOST_PLAYER_POINT - 100 * player_data->GetRankNum(other_player_tag);
		player_data->SetRankingPoint(other_player_tag, player_data->GetRankingPoint(other_player_tag) - point);
	}
	player_data->SetRankingPoint(_player_tag, player_data->GetRankingPoint(_player_tag) + point);
	return player_data->GetRankingPoint(_player_tag) + point;
}
