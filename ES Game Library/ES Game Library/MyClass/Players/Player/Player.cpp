#include "Player.h"
#include "../PlayerParametor/PlayerParametor.h"


Player::Player(std::string name, std::string arm_name)
{
	PlayerParametor::Instance().CreateParametor(name);
	arm = new Arm(name, arm_name);
	
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
	//�Q�[���p�b�h
	move_speed = 0.05f;

	player->SetScale(player_scale);

	arm->Initialize();

	return true;
}

int Player::Update()
{
	player_get_pos = player->GetPosition();
	player_get_rot = player->GetRotation();

	arm->Update();

	//���P�b�g�p���`
	if (ControllerManager::Instance().PadBuffer().IsPressed(GamePad_Button1) && arm->GetArmState() == NO_PUNCH)
	{
		arm->ArmShoot(PUNCH);
	}

	//�v���C���[�ړ�
	if (ControllerManager::Instance().PadState().X != Axis_Center && arm->GetArmState() == NO_PUNCH ||
		ControllerManager::Instance().PadState().Y != Axis_Center && arm->GetArmState() == NO_PUNCH)
	{
		Move();
	}

	return 0;
}

void Player::Move() 
{
	angle = MathHelper_Atan2(double(ControllerManager::Instance().PadState().X - Axis_Center) / double(Axis_Max - Axis_Center),
		-double(ControllerManager::Instance().PadState().Y - Axis_Center) / double(Axis_Max - Axis_Center));

	player->SetRotation(0, angle, 0);
	player->Move(0, 0, move_speed);

	arm->SetPra(player_get_pos, angle);
}