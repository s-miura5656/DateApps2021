#include "Player.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/Parametor.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include <codecvt>

Player::Player(std::string tag)
{
	PlayerParametor::Instance().CreateParametor(tag);
	
	_tag = tag;
	_arm_tag = ARM_TAG + std::to_string(GetTagNum(tag));
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(tag);
	_hit_box->SetHitBoxScale(0.8f);
	_i_player_data = new IPrayerData;
	_i_arm_Data    = new IArmData;
	_i_map_data    = new IMapData;
}

Player::~Player()
{
	_arm.reset();
	delete _i_map_data;
	delete _i_arm_Data;
	delete _i_player_data;
	_hit_box.reset();
}

bool Player::Initialize()
{

	//! file
	_font   = ResouceManager::Instance().LordFontFile(_T("SketchFlow Print"), 20);
	_model  = ResouceManager::Instance().LoadAnimationModelFile(_T("player/Robo_animation ver3.X"));
	_shader = ResouceManager::Instance().LordEffectFile(_T("HLSL/CharaShader.hlsl"));

	//! Position
	_model->SetPosition(_i_player_data->GetPosition(_tag));
	_position = _model->GetPosition();
	_old_pos = _position;
	_new_pos = _position;
	_index_num.Initialize(fabsf(_position.x), fabsf(_position.y), fabsf(_position.z));
	_i_player_data->SetIndexNum(_tag, _index_num);

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

	//! index
	_animation_index = _i_player_data->GetState(_tag);

	//! count
	_animation_count = 0;

	//! shader
	_model->RegisterBoneMatricesByName(_shader, "WorldMatrixArray", "NumBones");
	auto path = ConvertFilePath("Player/", _tag, ".png");
	_texture = GraphicsDevice.CreateSpriteFromFile(path.c_str());
	
	return true;
}

int Player::Update()
{
	auto pad = ControllerManager::Instance().GetController(_tag);
	pad->GamePadRefresh();

	DebugControll();

	//! ダメージ状態の判定
	if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::DAMAGE)
	{
		_damage_count++;

		if (_damage_count > 120)
		{
			_i_player_data->SetState(_tag, PlayerEnum::Animation::MOVE);
			_damage_count = 0;
		}

		DestroyArm();

		return 0;
	}
	
	//! 移動中か待機中か判定
	if (!_move_flag)
	{
		//! パンチ発射状態ならすぐさまリターン
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

			//! プレイヤー移動
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

			//! ロケットパンチ発射切り替え
			if (pad->GetButtonState(GamePad_Button2))
			{
				_i_player_data->SetState(_tag, PlayerEnum::Animation::SHOT);
				_i_player_data->SetPosition(_tag, _position);
			}
		}
	}

	if (_i_player_data->GetState(_tag) == PlayerEnum::Animation::MOVE)
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


	//! アームの飛ぶ速度調整
	float speed = _i_arm_Data->GetGoSpeed(_arm_tag);

	if (keybuffer.IsPressed(Keys_Up) && keystate.IsKeyDown(Keys_LeftControl))
		speed += 0.01f;

	if (keybuffer.IsPressed(Keys_Down) && keystate.IsKeyDown(Keys_LeftControl))
		speed -= 0.01f;

	speed = Clamp(speed, 0.01f, 10.0f);
	_i_arm_Data->SetGoSpeed(_arm_tag, speed);


	//! アームの戻る速度調整
	speed = _i_arm_Data->GetReturnSpeed(_arm_tag);

	if (keybuffer.IsPressed(Keys_Up) && keystate.IsKeyDown(Keys_LeftAlt))
		speed += 0.01f;

	if (keybuffer.IsPressed(Keys_Down) && keystate.IsKeyDown(Keys_LeftAlt))
		speed -= 0.01f;

	speed = Clamp(speed, 0.01f, 10.0f);
	_i_arm_Data->SetReturnSpeed(_arm_tag, speed);


	//! プレイヤーの移動速度調整
	speed = _i_player_data->GetSpeed(_tag);

	if (keybuffer.IsPressed(Keys_Up) && keystate.IsKeyDown(Keys_LeftShift))
		speed += 0.01f;

	if (keybuffer.IsPressed(Keys_Down) && keystate.IsKeyDown(Keys_LeftShift))
		speed -= 0.01f;

	speed = Clamp(speed, 0.01f, 10.0f);
	_i_player_data->SetSpeed(_tag, speed);


	//! アームの限界距離
	int range = _i_arm_Data->GetLimitRange(_arm_tag);

	if (keybuffer.IsPressed(Keys_Right))
		range++;

	if (keybuffer.IsPressed(Keys_Left))
		range--;

	range = (int)Clamp(range, 1, 20);

	_i_arm_Data->SetLimitRange(_arm_tag, range);
}


