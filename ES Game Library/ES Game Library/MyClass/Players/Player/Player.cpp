#include "Player.h"
#include "../../Data/Parametor.h"
#include "../../Data/MyAlgorithm.h"

Player::Player(std::string tag)
{
	PlayerParametor::Instance().CreateParametor(tag);
	
	_tag = tag;
	_arm_tag = ARM_TAG + std::to_string(GetTagNum(tag));
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(tag);
	_hit_box->SetHitBoxScale(0.7f);
	_iplayer_data = new IPrayerData;
	_iarm_data = new IArmData;
	_imap_data = new IMapData;
}

Player::~Player()
{
	if (_arm != nullptr)
		delete _arm;
	
	delete _imap_data;
	delete _iarm_data;
	delete _iplayer_data;
	_hit_box->OnReMove();
}

bool Player::FileInitialize(LPCTSTR& file)
{
	_model = GraphicsDevice.CreateModelFromFile(file);
	return true;
}

bool Player::Initialize()
{
	_font = GraphicsDevice.CreateSpriteFont(_T("SketchFlow Print"), 50);

	_model->SetScale(player_scale);

	_model->SetPosition(_iplayer_data->GetPosition(_tag));

	_position = _model->GetPosition();
	_old_pos = _position;
	_new_pos = _position;
	
	Vector3 position = _position;

	_index_num.Initialize(fabsf(_position.x), fabsf(_position.y), fabsf(_position.z));
	
	_iplayer_data->SetIndexNum(_tag, _index_num);
	_iarm_data->SetSpeed(_arm_tag, 0.1f);
	ControllerManager::Instance().CreateGamePad(_tag);

	return true;
}

int Player::Update()
{
	auto pad = ControllerManager::Instance().GetController(_tag);
	pad->GamePadRefresh();

	KeyboardBuffer keybuffer = Keyboard->GetBuffer();

	if (keybuffer.IsPressed(Keys_Up))
	{
		float speed = _iarm_data->GetSpeed(_arm_tag);
		speed += 0.01f;
		_iarm_data->SetSpeed(_arm_tag, speed);
	}

	if (keybuffer.IsPressed(Keys_Down))
	{
		float speed = _iarm_data->GetSpeed(_arm_tag);
		speed -= 0.01f;
		_iarm_data->SetSpeed(_arm_tag, speed);
	}

	if (_iplayer_data->GetState(_tag) == PlayerEnum::DAMAGE)
	{
		_index_num = _iplayer_data->GetIndexNum(_tag);
		_position = Vector3(1 * _index_num.x, 0, 1 * -_index_num.z);
		_model->SetPosition(_position);
		_iplayer_data->SetState(_tag, PlayerEnum::WAIT);
		return 0;
	}

	if (_iplayer_data->GetState(_tag) == PlayerEnum::MOVE)
	{
		//! 移動
		Move(pad);
	}

	//! パンチ発射状態ならすぐさまリターン
	if (_iplayer_data->GetState(_tag) == PlayerEnum::ATTACK)
	{
		_iplayer_data->SetIndexNum(_tag, _index_num);
		_arm->Update();
		return 0;
	}

	if (_iplayer_data->GetState(_tag) == PlayerEnum::WAIT)
	{
		DestroyArm();

		//! ロケットパンチ発射切り替え
		if (pad->GetButtonState(GamePad_Button1))
		{
			_iplayer_data->SetState(_tag, PlayerEnum::ATTACK);
			CreateArm();
			return 0;
		}
	}
	
	//! プレイヤー移動
	if (pad->GetPadStateX() != Axis_Center || pad->GetPadStateY() != Axis_Center)
	{
		_angle = AngleCalculating(pad->GetPadStateX(), pad->GetPadStateY());
		_angle = AngleClamp(_angle);
		_iplayer_data->SetState(_tag, PlayerEnum::MOVE);
	}

	return 0;
}

void Player::Move(Controller* pad)
{
	auto&& map_data = _imap_data->GetData();

	if (_move_flag)
	{
		_position = Vector3_Lerp(_old_pos, _new_pos, _lerp_count);
		_lerp_count += 0.04f;

		if (_lerp_count >= 1.f)
		{
			_move_flag = false;
			_lerp_count = 0;
			_iplayer_data->SetState(_tag, PlayerEnum::WAIT);
		}
	}
	else
	{
		float abs_x = fabsf(pad->GetPadStateX());
		
		float abs_z = fabsf(pad->GetPadStateY());

		if (abs_x > 16 && abs_x > abs_z)
		{
			int old_index = _index_num.x;

			std::signbit(pad->GetPadStateX()) ? _index_num.x-- : _index_num.x++;

			_index_num.x = Clamp(_index_num.x, 1, map_data[_index_num.z].size() - 3);

			if (map_data[_index_num.z][_index_num.x] != 'i' && 
				map_data[_index_num.z][_index_num.x] != 'w')
			{
				_new_pos = Vector3(1 * _index_num.x, 0, 1 * -_index_num.z);
				_move_flag = true;
			}
			else
			{
				_index_num.x = old_index;
			}
		}

		if (abs_z > 16 && abs_x < abs_z)
		{
			int old_index = _index_num.z;

			std::signbit(pad->GetPadStateY()) ? _index_num.z-- : _index_num.z++;

			_index_num.z = Clamp(_index_num.z, 1, map_data.size() - 2);

			if (map_data[_index_num.z][_index_num.x] != 'i' && 
				map_data[_index_num.z][_index_num.x] != 'w')
			{
				_new_pos = Vector3(1 * _index_num.x, 0, 1 * -_index_num.z);
				_iplayer_data->SetIndexNum(_tag , _index_num);
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
