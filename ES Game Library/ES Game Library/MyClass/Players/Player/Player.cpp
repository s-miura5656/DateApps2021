#include "Player.h"
#include "../PlayerParametor/PlayerParametor.h"
#include "../../Managers/ControllerManager/ContorollerManager.h"

Player::Player(std::string name)
{
	PlayerParametor::Instance().CreateParametor(name);
	arm = new Arm(name);
	_tag = name;
	_hit_box.reset(new HitBox());
	_hit_box->Init();
	_hit_box->Settags(name);
}

Player::~Player()
{
	delete arm;
}

bool Player::FileInitialize(LPCTSTR& file)
{
	player = GraphicsDevice.CreateModelFromFile(file);
	return true;
}

bool Player::Initialize()
{
	//ゲームパッド
	move_speed = 0.05f;

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
	if (ControllerManager::Instance().GetController(_tag)->GetButtonBuffer(GamePad_Button1) && arm->GetArmState() == NO_PUNCH)
	{
		arm->ArmShoot(PUNCH);
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

	angle = MathHelper_Atan2(double(pad->GetPadStateX() - Axis_Center) / double(Axis_Max - Axis_Center),
		-double(pad->GetPadStateY() - Axis_Center) / double(Axis_Max - Axis_Center));

	player->SetRotation(0, angle, 0);
	player->Move(0, 0, move_speed);

	arm->SetPra(player_get_pos, angle);
}