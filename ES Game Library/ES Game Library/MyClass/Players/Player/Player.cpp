#include "Player.h"
#include "../PlayerParametor/PlayerParametor.h"


Player::Player(std::string name)
{
	PlayerParametor::Instance().CreateParametor(name);
	arm = new Arm(name);
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

	

	// @brief プレイヤーの当たり判定用の箱
	//player_obb = player->GetOBB();
	//player_obb.Radius.x *= 0.33333f;
	//
	//shape.Type = Shape_Box;
	//shape.Width = player_obb.Radius.x * 2.0f;
	//shape.Height = player_obb.Radius.y * 2.0f;
	//shape.Depth = player_obb.Radius.z * 2.0f;
	//player_hitbox = GraphicsDevice.CreateModelFromSimpleShape(shape);

	return true;
}

int Player::Update()
{
	/*pad_state = GamePad(pad_number)->GetState();
	pad_buffer = GamePad(pad_number)->GetBuffer();*/

	player_get_pos = player->GetPosition();
	player_get_rot = player->GetRotation();

	arm->Update();

	//ロケットパンチ
	if (controller.PadBuffer().IsPressed(GamePad_Button1) && arm->GetArmState() == NO_PUNCH)
	{
		arm->ArmShoot(PUNCH);
	}

	//プレイヤー移動
	if (controller.PadState().X != Axis_Center && arm->GetArmState() == NO_PUNCH ||
		controller.PadState().Y != Axis_Center && arm->GetArmState() == NO_PUNCH)
	{
		Move();
	}


	// @brief プレイヤーとブロック・素材の当たり判定の座標補正
	//player_obb.Center = player_get_pos;
	//player_obb.Center.y = player_obb.Radius.y;
	//player_obb.SetAxis(player->GetDirectionQuaternion());

	return 0;
}

void Player::Move() 
{
	angle = MathHelper_Atan2(double(controller.PadState().X - Axis_Center) / double(Axis_Max - Axis_Center),
		-double(controller.PadState().Y - Axis_Center) / double(Axis_Max - Axis_Center));

	player->SetRotation(0, angle, 0);
	player->Move(0, 0, move_speed);

	arm->SetPra(player_get_pos, angle);
}