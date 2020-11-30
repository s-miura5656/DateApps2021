#include "Player.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/Parametor.h"
#include "../../Managers/ResouceManager/ResouceManager.h"

Player::Player(std::string tag)
{
	PlayerParametor::Instance().CreateParametor(tag);
	
	_tag = tag;
	_arm_tag = ARM_TAG + std::to_string(GetTagNum(tag));
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(tag);
	_hit_box->SetHitBoxScale(0.8f);
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

bool Player::Initialize()
{
	//! file
	_font = GraphicsDevice.CreateSpriteFont(_T("SketchFlow Print"), 50);
	_model = GraphicsDevice.CreateAnimationModelFromFile(_T("player/robot.X"));


	//! Position
	_model->SetPosition(_iplayer_data->GetPosition(_tag));
	_position = _model->GetPosition();
	_old_pos = _position;
	_new_pos = _position;
	_index_num.Initialize(fabsf(_position.x), fabsf(_position.y), fabsf(_position.z));
	_iplayer_data->SetIndexNum(_tag, _index_num);

	//! Speed
	_iarm_data->SetSpeed(_arm_tag, 0.1f);

	//! Scale
	_model->SetScale(player_scale);

	//! Pad
	ControllerManager::Instance().CreateGamePad(_tag);

	//! Material
	Material mat;
	mat.Diffuse = Color(1.0f, 1.0f, 1.0f);
	mat.Ambient = Color(1.0f, 1.0f, 1.0f);
	mat.Specular = Color(1.0f, 1.0f, 1.0f);

	_model->SetMaterial(mat);

	return true;
}

int Player::Update()
{
	auto pad = ControllerManager::Instance().GetController(_tag);
	pad->GamePadRefresh();

	ChangeAnimation();

	DebugControll();

	if (_iplayer_data->GetState(_tag) == PlayerEnum::Animation::DAMAGE)
	{
		_index_num = _iplayer_data->GetIndexNum(_tag);
		_position = Vector3(1 * _index_num.x, 0, 1 * -_index_num.z);
		_model->SetPosition(_position);
		_iplayer_data->SetState(_tag, PlayerEnum::Animation::WAIT);
		return 0;
	}
	
	if (_iplayer_data->GetState(_tag) == PlayerEnum::Animation::WAIT)
	{
		DestroyArm();

		//! ロケットパンチ発射切り替え
		if (pad->GetButtonState(GamePad_Button2))
		{
			_iplayer_data->SetState(_tag, PlayerEnum::Animation::ATTACK);
			_iplayer_data->SetPosition(_tag, _position);
			CreateArm();
			return 0;
		}

		//! プレイヤー移動
		if (pad->GetPadStateX() != Axis_Center || pad->GetPadStateY() != Axis_Center)
		{
			_angle = AngleCalculating(pad->GetPadStateX(), pad->GetPadStateY());
			_angle = AngleClamp(_angle);
			_iplayer_data->SetState(_tag, PlayerEnum::Animation::MOVE);
		}
	}

	//! パンチ発射状態ならすぐさまリターン
	if (_iplayer_data->GetState(_tag) == PlayerEnum::Animation::ATTACK)
	{
		_iplayer_data->SetIndexNum(_tag, _index_num);
		_arm->Update();
		return 0;
	}

	if (_iplayer_data->GetState(_tag) == PlayerEnum::Animation::MOVE)
	{
		//! 移動
		Move(pad);
	}
	
	return 0;
}

void Player::DebugControll()
{
	KeyboardBuffer keybuffer = Keyboard->GetBuffer();
	KeyboardState keystate   = Keyboard->GetState();

	//! アームの移動速度調整
	float speed = _iarm_data->GetSpeed(_arm_tag);

	if (keybuffer.IsPressed(Keys_Up))
		speed += 0.01f;

	if (keybuffer.IsPressed(Keys_Down))
		speed -= 0.01f;

	speed = Clamp(speed, 0.01f, 10.0f);
	_iarm_data->SetSpeed(_arm_tag, speed);

	//! プレイヤーの移動速度調整
	speed = _iplayer_data->GetSpeed(_tag);

	if (keybuffer.IsPressed(Keys_Up) && keystate.IsKeyDown(Keys_LeftControl))
		speed += 0.01f;

	if (keybuffer.IsPressed(Keys_Down) && keystate.IsKeyDown(Keys_LeftControl))
		speed -= 0.01f;

	speed = Clamp(speed, 0.01f, 10.0f);
	_iplayer_data->SetSpeed(_tag, speed);

	//! アームの限界距離
	int range = _iarm_data->GetLimitRange(_arm_tag);

	if (keybuffer.IsPressed(Keys_Up) && keystate.IsKeyDown(Keys_LeftAlt))
		range++;

	if (keybuffer.IsPressed(Keys_Down) && keystate.IsKeyDown(Keys_LeftAlt))
		range--;

	range = (int)Clamp(range, 1, 20);

	_iarm_data->SetLimitRange(_arm_tag, range);
}


