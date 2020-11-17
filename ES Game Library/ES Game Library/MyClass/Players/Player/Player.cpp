#include "Player.h"
#include "../../Data/Parametor.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"
#include "../../Data/MyAlgorithm.h"

Player::Player(std::string tag)
{
	PlayerParametor::Instance().CreateParametor(tag);
	_arm = new Arm(tag);
	_tag = tag;
	_arm_tag = ARM_TAG + std::to_string(GetTagNum(tag));
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(tag);
	_hit_box->SetHitBoxScale(0.7f);
	_iplayer_data = new IPrayerData;
	_iarm_data = new IArmData;
}

Player::~Player()
{
	delete _iarm_data;
	delete _iplayer_data;
	delete _arm;
}

bool Player::FileInitialize(LPCTSTR& file)
{
	_player = GraphicsDevice.CreateModelFromFile(file);
	return true;
}

bool Player::Initialize()
{
	_font = GraphicsDevice.CreateSpriteFont(_T("SketchFlow Print"), 50);

	_player->SetScale(player_scale);

	_arm->Initialize();

	ControllerManager::Instance().CreateGamePad(_tag);

	return true;
}

int Player::Update()
{
	player_get_pos = _player->GetPosition();
	player_get_rot = _player->GetRotation();

	_arm->Update();

	auto pad = ControllerManager::Instance().GetController(_tag);

	//ロケットパンチ
	if (pad->GetButtonState(GamePad_Button1) && _arm->GetArmState() == NO_PUNCH)
	{
		_arm->ArmShoot(PUNCH);
	}
	else if (!pad->GetButtonState(GamePad_Button1) && _arm->GetArmState() == PUNCH)
	{
		_arm->ArmShoot(RETURN_PUNCH);
	}

	//プレイヤー移動
	if (pad->GetPadStateX() != Axis_Center && _arm->GetArmState() == NO_PUNCH ||
		pad->GetPadStateY() != Axis_Center && _arm->GetArmState() == NO_PUNCH)
	{
		auto list = _hit_box->IsHitBoxList(_arm_tag);

		if (list.empty())
		{
			Move();
		}
		else
		{
			auto it = list.begin();
			Vector3  P = Vector3(0.0f,0.0f,0.0f);
			P = SlidingOnWallVectorCreate((*it)->GetModelTag(), _player->GetPosition(), _player->GetFrontVector());
			Vector3 pos = _player->GetPosition();
			pos += P * 0.02f;
			_player->SetPosition(pos);
		}
	}

	return 0;
}

void Player::Move() 
{
	auto pad = ControllerManager::Instance().GetController(_tag);

	auto a = double(pad->GetPadStateX() - Axis_Center) / double(Axis_Max);

	auto b = -double(pad->GetPadStateY() - Axis_Center) / double(Axis_Max);

	auto x = Clamp(pad->GetPadStateX(), -0.1f, 0.1f);

	auto z = -Clamp(pad->GetPadStateY(), -0.1f, 0.1f);

	_angle = MathHelper_Atan2(a, b);

	_player->SetRotation(0, _angle, 0);

	auto pos = _iplayer_data->GetPosition(_tag) + Vector3(x, 0, z);

	_player->SetPosition(pos);

	_arm->SetPra(player_get_pos, _angle);
}

