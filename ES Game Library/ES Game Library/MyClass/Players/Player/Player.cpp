#include "Player.h"
#include "../../Data/Parametor.h"
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

	_player->SetPosition(_iplayer_data->GetPosition(_tag));

	ControllerManager::Instance().CreateGamePad(_tag);

	return true;
}

int Player::Update()
{
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
		_angle = AngleCalculating(pad->GetPadStateX(), pad->GetPadStateY());
		_player->SetRotation(0, _angle, 0);

		auto hit_list = _hit_box->IsHitBoxList(_arm_tag);

		if (!hit_list.empty())
		{
			_position = _player->GetPosition() + _hit_box->WallShavingObjects(hit_list, _position, _player->GetFrontVector()) * 0.05f;
			_player->SetPosition(_position);
			_arm->SetPra(_position, _angle);
		}
		else
		{
			_position = Move(pad->GetPadStateX(), pad->GetPadStateY());
			_player->SetPosition(_position);
			_arm->SetPra(_position, _angle);
		}

		_old_pos = _position;
	}

	return 0;
}

Vector3 Player::Move(float pad_x, float pad_y)
{
	auto x = Clamp(pad_x, -0.1f, 0.1f);

	auto z = -Clamp(pad_y, -0.1f, 0.1f);

	auto pos = _iplayer_data->GetPosition(_tag) + Vector3(x, 0, z);

	return pos;
}

