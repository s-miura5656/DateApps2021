#include "Player.h"
#include "../PlayerParametor/PlayerParametor.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"

Player::Player(std::string name)
{
	PlayerParametor::Instance().CreateParametor(name);
	arm = new Arm(name);
	_tag = name;
	_arm_tag = ARM_TAG + std::to_string(GetTagNum(_tag));
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(name);
	_hit_box->SetHitBoxScale(0.7f);
	_iplayer_data = new IPrayerData;
	_iarm_data = new IArmData;
}

Player::~Player()
{
	delete _iarm_data;
	delete _iplayer_data;
	delete arm;
}

bool Player::FileInitialize(LPCTSTR& file)
{
	player = GraphicsDevice.CreateModelFromFile(file);
	return true;
}

bool Player::Initialize()
{
	player->SetScale(player_scale);

	arm->Initialize();

	ControllerManager::Instance().CreateGamePad(_tag);

	return true;
}

int Player::Update()
{
	player_get_pos = player->GetPosition();
	player_get_rot = player->GetRotation();

	arm->Update();

	auto pad = ControllerManager::Instance().GetController(_tag);

	//ロケットパンチ
	if (pad->GetButtonState(GamePad_Button1) && arm->GetArmState() == NO_PUNCH)
	{
		arm->ArmShoot(PUNCH);
	}
	else if (!pad->GetButtonState(GamePad_Button1) && arm->GetArmState() == PUNCH)
	{
		arm->ArmShoot(RETURN_PUNCH);
	}

	//プレイヤー移動
	if (pad->GetPadStateX() != Axis_Center && arm->GetArmState() == NO_PUNCH ||
		pad->GetPadStateY() != Axis_Center && arm->GetArmState() == NO_PUNCH)
	{
		Move();
	}

	return 0;
}

void Player::Move() 
{
	auto pad = ControllerManager::Instance().GetController(_tag);

	auto a = double(pad->GetPadStateX() - Axis_Center) / double(Axis_Max);

	auto b = -double(pad->GetPadStateY() - Axis_Center) / double(Axis_Max);

	auto x = pad->GetPadStateX();

	auto y = pad->GetPadStateY();

	angle = MathHelper_Atan2(a, b);

	player->SetRotation(0, angle, 0);

	player->Move(0, 0, PlayerSpeed());

	arm->SetPra(player_get_pos, angle);
}

