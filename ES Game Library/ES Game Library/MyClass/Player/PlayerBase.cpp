#include "PlayerBase.h"

bool PlayerBase::FileInitialize(LPCTSTR file)
{
	player = GraphicsDevice.CreateModelFromFile(file);
	rocket_punch = GraphicsDevice.CreateModelFromFile(_T("Player/sword_01.X"));
	return 0;
}

bool PlayerBase::Initialize(int pad_num, Vector3 pos,Material mat)
{
	//プレイヤーの状態
	
	//ゲームパッド
	pad_number = pad_num;

	move_speed = 0.05;

	player->SetPosition(pos);
	
	player->SetMaterial(mat);

	
	rocket_punch->SetMaterial(mat);

	scale = 0.005;

	punch_state = NO_PUNCH;

	punch_spped = 0.1;

	// @brief プレイヤーの当たり判定用の箱
	player_obb = player->GetOBB();
	player_obb.Radius.x *= 0.33333f;

	shape.Type = Shape_Box;
	shape.Width = player_obb.Radius.x * 2.0f;
	shape.Height = player_obb.Radius.y * 2.0f;
	shape.Depth = player_obb.Radius.z * 2.0f;
	player_hitbox = GraphicsDevice.CreateModelFromSimpleShape(shape);
	
	return 0;
}

void PlayerBase::Update()
{
	pad_state  = GamePad(pad_number)->GetState();
	pad_buffer = GamePad(pad_number)->GetBuffer();

	player_get_pos = player->GetPosition();
	player_get_rot = player->GetRotation();
	punch_get_pos  = rocket_punch->GetPosition();
	punch_get_rot  = rocket_punch->GetRotation();
	
	float dist = Vector3_Distance(player_get_pos, punch_get_pos);

	
	//ロケットパンチ
	if (pad_buffer.IsPressed(GamePad_Button1) && punch_state == NO_PUNCH)
	{
		punch_state = PUNCH;
	}

	if (punch_state == RETURN_PUNCH)
	{
		rocket_punch->Move(0, 0, -punch_spped);
		if (dist <= 0.5) {
			punch_state = NO_PUNCH;
			dist = 0;
		}
	}
	else if (punch_state == PUNCH)
	{
		rocket_punch->Move(0, 0, punch_spped);
		if (dist >= 5)
		{
			dist = 5;
			punch_state = RETURN_PUNCH;
		}
	}
	else if (punch_state == NO_PUNCH)
	{
		rocket_punch->SetPosition(player_get_pos);
	}

	
	//プレイヤー移動
	if (pad_state.X != Axis_Center && punch_state == NO_PUNCH ||
		pad_state.Y != Axis_Center && punch_state == NO_PUNCH )
	{
		angle = MathHelper_Atan2(double(pad_state.X - Axis_Center) / double(Axis_Max - Axis_Center),
			-double(pad_state.Y - Axis_Center) / double(Axis_Max - Axis_Center));

		player->SetRotation(0, angle, 0);
		player->Move(0, 0, move_speed);

		rocket_punch->SetRotation(0, angle, 0);
		rocket_punch->SetPosition(player_get_pos);
	}
	

	// @brief プレイヤーとブロック・素材の当たり判定の座標補正
	player_obb.Center = player_get_pos;
	player_obb.Center.y = player_obb.Radius.y;
	player_obb.SetAxis(player->GetDirectionQuaternion());

}

void PlayerBase::Draw()
{
	
	player->SetScale(scale);
	player->Draw();
	
	// @brief プレイヤーの当たり判定の描画
	player_hitbox->SetPosition(player_obb.Center);
	player_hitbox->SetDirection(player->GetDirectionQuaternion());
	player_hitbox->SetScale(scale);
	player_hitbox->Draw();

	rocket_punch->SetScale(0.01);
	rocket_punch->Draw();

}
