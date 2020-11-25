#pragma once

#include"../../ESGLib.h"

class Controller
{
public:
	Controller(int number) 
	{
		pad_number = number; 
	}

	~Controller() {}

	bool Initialize();
	void Update();

	GamePadBuffer PadBuffer();

	bool GetButtonBuffer(int button_num) { return PadBuffer().IsPressed(button_num); }

	GamePadState PadState();

	bool GetButtonState(int button_num) { return PadState().Buttons[button_num - GamePad_Button1]; }


	float GetPadStateX() { return PadState().X / move_value_constant; }

	float GetPadStateY() { return PadState().Y / move_value_constant; }


	KeyboardState KeyState() { return Keyboard->GetState(); }

	bool KeyboardButtonState(int button_num) { return _key_state.IsKeyDown(button_num); }

	bool KeyboardButtonBuffer(int button_num) { return _key_buffer.IsPressed(button_num); }

	static void GetKeyboardBuffer() {  }

private:
	int _pad_number;
	int const move_value_constant = 1000;

	KeyboardBuffer _key_buffer;
	KeyboardState  _key_state;
};