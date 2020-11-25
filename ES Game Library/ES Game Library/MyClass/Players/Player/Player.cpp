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

	ControllerManager::Instance().CreateGamePad(_tag);

	return true;
}

int Player::Update()
{
	//! パンチ発射状態ならすぐさまリターン
	if (_iplayer_data->GetState(_tag) == PlayerEnum::ATTACK)
	{
		_arm->Update();
		return 0;
	}

	if (_iplayer_data->GetState(_tag) == PlayerEnum::WAIT)
	{
		DestroyArm();
	}

	auto pad = ControllerManager::Instance().GetController(_tag);

	//! ロケットパンチ発射切り替え
	if (pad->GetButtonBuffer(GamePad_Button1))
	{
		a++;
		_iplayer_data->SetState(_tag, PlayerEnum::ATTACK);
		CreateArm();
		return 0;
	}

	//! プレイヤー移動
	if (pad->GetPadStateX() != Axis_Center || pad->GetPadStateY() != Axis_Center)
	{
		_iplayer_data->SetState(_tag, PlayerEnum::MOVE);

		//! 移動
		Move(pad);
	}
	else
	{
		_iplayer_data->SetState(_tag, PlayerEnum::WAIT);
	}

	return 0;
}

void Player::Move(Controller* pad)
{
	_angle = AngleCalculating(pad->GetPadStateX(), pad->GetPadStateY());
	_model->SetRotation(0, _angle, 0);

#pragma region 移動と当たり判定
	auto hit_list = _hit_box->IsHitBoxList(_arm_tag);

	Vector3 move_dir = Vector3_Zero;

	auto map_pos = _imap_data->GetPosition();

	if (!hit_list.empty())
	{
		auto model = _hit_box->IshitNearestObject(hit_list, _position, _model->GetFrontVector());

		auto hit_box = _hit_box->GetModelTag();

		if (hit_box->GetPosition().x + hit_box->GetScale().x / 2 > model->GetPosition().x - model->GetScale().x / 2 ||
			hit_box->GetPosition().x - hit_box->GetScale().x / 2 < model->GetPosition().x + model->GetScale().x / 2 ||
			hit_box->GetPosition().z + hit_box->GetScale().z / 2 < model->GetPosition().z - model->GetScale().z / 2 ||
			hit_box->GetPosition().z - hit_box->GetScale().z / 2 < model->GetPosition().z + model->GetScale().z / 2)
		{
			_position = _old_pos;
		}

		_model->SetPosition(_position);

		move_dir = SlidingOnWallVectorCreate(model, _model->GetPosition(), _model->GetFrontVector());

		_position += move_dir * 0.04f;
	}
	else
	{
		move_dir = MoveDirection(pad->GetPadStateX(), pad->GetPadStateY());
		move_dir *= 0.04f;
		_position = _model->GetPosition() + move_dir;
	}
#pragma endregion


	_model->SetPosition(_position);

	_old_pos = _position;
}
