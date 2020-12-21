#include "InputManager.h"

#pragma comment(lib,"xinput.lib")

#pragma region InputManager
InputManager::InputManager()
{
	_pad_num	= 0;
	_xpad_count = 0;
	_dpad_count = 0;
}

InputManager::~InputManager()
{
	for (auto& it = _game_pads.rbegin(); it != _game_pads.rend(); ++it)
	{
		(*it).second.reset();
	}
}

void InputManager::CreateXInputGamePad(std::string tag)
{
	for (int pad_num = 0; pad_num < PAD_COUNT_MAX; ++pad_num)
	{
		if (XInputActive(pad_num))
		{
			auto name_tag = tag;
			name_tag = name_tag + std::to_string(pad_num + 1);
			_game_pads.emplace(name_tag, std::make_unique<XInput>(pad_num));
		}
	}
}

void InputManager::CreateDInputGamePad(std::string tag, int pad_count)
{
	InputDevice.CreateGamePad(pad_count);

	for (int pad_num = 1; pad_num <= pad_count; ++pad_num)
	{
		auto name_tag = tag;
		name_tag = name_tag + std::to_string(pad_num);
		_game_pads.emplace(name_tag, std::make_unique<DirectInput>(pad_num));
	}
}

BaseInput* InputManager::GetGamePad(std::string tag)
{
	return _game_pads[tag].get();
}

bool InputManager::XInputActive(int pad_num)
{
	DWORD dwResult;

	XINPUT_STATE x_state;

	ZeroMemory(&x_state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(pad_num, &x_state);

	bool activation = (dwResult == ERROR_SUCCESS);

	return activation;
}
#pragma endregion

#pragma region XInput
XInput::XInput(int pad_number) 
{
	_pad_number = pad_number;

	for (int i = 0; i < BUTTON_INFO::MAX_BUTTON_INFO; ++i)
	{
		_button_enter_flag[i] = false;
	}
	
	_button_exit_flag = true;

	_button_info[0]  = XINPUT_GAMEPAD_A;
	_button_info[1]  = XINPUT_GAMEPAD_B;
	_button_info[2]  = XINPUT_GAMEPAD_Y;
	_button_info[3]  = XINPUT_GAMEPAD_X;
	_button_info[4]  = XINPUT_GAMEPAD_START;
	_button_info[5]  = XINPUT_GAMEPAD_BACK;
	_button_info[6]  = XINPUT_GAMEPAD_LEFT_SHOULDER;
	_button_info[7]  = XINPUT_GAMEPAD_RIGHT_SHOULDER;
	_button_info[8]  = XINPUT_GAMEPAD_LEFT_THUMB;
	_button_info[9]  = XINPUT_GAMEPAD_RIGHT_THUMB;
	_button_info[10] = XINPUT_GAMEPAD_DPAD_UP;
	_button_info[11] = XINPUT_GAMEPAD_DPAD_DOWN;
	_button_info[12] = XINPUT_GAMEPAD_DPAD_LEFT;
	_button_info[13] = XINPUT_GAMEPAD_DPAD_RIGHT;

	for (auto& state : _button_state)
	{
		state = INPUT_STATE::NOT_PUSH;
	}

	XInputEnable(TRUE);
}

XInput::~XInput()
{
	XInputEnable(FALSE);
}

void XInput::Refresh()
{
	_x_state = GetXState();
}

bool XInput::Button(int key_info)
{
	InputButtonState(key_info);
	return _button_state[key_info] == INPUT_STATE::PUSH;
}

bool XInput::ButtonDown(int key_info)
{
	InputButtonState(key_info);

	if (_button_state[key_info] == INPUT_STATE::PUSH)
	{
		if (_button_enter_flag[key_info])
		{
			return false;
		}
		else
		{
			return _button_enter_flag[key_info] = true;
		}
	}
	else
	{
		return _button_enter_flag[key_info] = false;
	}
}

bool XInput::ButtonUp(int key_info)
{
	InputButtonState(key_info);

	if (_button_state[key_info] == INPUT_STATE::PUSH)
	{
		return _button_exit_flag = false;
	}
	else
	{
		if (_button_exit_flag)
		{
			return false;
		}
		else
		{
			return _button_exit_flag = true;
		}
	}
}

float XInput::Trigger(int key_info)
{
	//auto x_state = GetXState();

	if (key_info == TRIGGER_INFO::LEFT_TRIGGER)
	{
		return _x_state.Gamepad.bLeftTrigger;
	}
	else if (key_info == TRIGGER_INFO::RIGHT_TRIGGER) 
	{
		return _x_state.Gamepad.bRightTrigger;
	}
}

Vector2 XInput::Stick(int key_info)
{
	_x_state = GetXState();

	Vector2 stick = Vector2_Zero;

	if (key_info == STICK_INFO::LEFT_STICK)
	{
		stick.x = _x_state.Gamepad.sThumbLX;
		stick.y = _x_state.Gamepad.sThumbLY;
		
	}
	else if (key_info == STICK_INFO::RIGHT_STICK)
	{
		stick.x = _x_state.Gamepad.sThumbRX;
		stick.y = _x_state.Gamepad.sThumbRY;
	}

	if ((stick.x <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		 stick.x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		stick.x = 0;
	}

	if ((stick.y <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		 stick.y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		stick.y = 0;
	}

	return stick;
}

INPUT_STATE XInput::InputButtonState(int key_info)
{
	return 	_button_state[key_info] = _x_state.Gamepad.wButtons & _button_info[key_info] ? INPUT_STATE::PUSH : INPUT_STATE::NOT_PUSH;
}

XINPUT_STATE XInput::GetXState()
{
	XINPUT_STATE x_state;

	ZeroMemory(&x_state, sizeof(XINPUT_STATE));

	XInputGetState(_pad_number, &x_state);

	return x_state;
}
#pragma endregion

#pragma region DirectInput
DirectInput::DirectInput(int pad_number)
{
	_pad_number = pad_number - 1;

	_button_info[0]  = GamePad_Button2;
	_button_info[1]  = GamePad_Button3;
	_button_info[2]  = GamePad_Button4;
	_button_info[3]  = GamePad_Button1;
	_button_info[4]  = GamePad_Button10;
	_button_info[5]  = GamePad_Button9;
	_button_info[6]  = GamePad_Button5;
	_button_info[7]  = GamePad_Button6;
	_button_info[8]  = GamePad_Button11;
	_button_info[9]  = GamePad_Button12;
	_button_info[10] = GamePad_POV1;
	_button_info[11] = GamePad_POV2;
	_button_info[12] = GamePad_POV3;
	_button_info[13] = GamePad_POV4;

	_trigger_info[0] = GamePad_Button7;
	_trigger_info[1] = GamePad_Button8;
}

DirectInput::~DirectInput()
{

}

void DirectInput::Refresh()
{
	_pad_buffer = GamePad(_pad_number)->GetBuffer();
	_pad_state  = GamePad(_pad_number)->GetState();
}

bool DirectInput::Button(int key_info)
{
	return _pad_state.Buttons[_button_info[key_info] - GamePad_Button1];
}

bool DirectInput::ButtonDown(int key_info)
{
	return _pad_buffer.IsPressed(_button_info[key_info]);
}

bool DirectInput::ButtonUp(int key_info)
{
	return _pad_buffer.IsReleased(_button_info[key_info]);
}

float DirectInput::Trigger(int key_info)
{
	return _pad_state.Buttons[_trigger_info[key_info] - GamePad_Button1];
}

Vector2 DirectInput::Stick(int key_info)
{
	Vector2 stick = Vector2_Zero;

	stick.x = _pad_state.X / move_value_constant;

	stick.y = -_pad_state.Y / move_value_constant;

	return stick;
}
#pragma endregion