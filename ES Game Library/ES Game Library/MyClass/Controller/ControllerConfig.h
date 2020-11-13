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

	GamePadBuffer PadBuffer() { return GamePad(pad_number)->GetBuffer(); }

	bool GetButtonBuffer(int button_num) { return PadBuffer().IsPressed(button_num); }

	GamePadState PadState() { return GamePad(pad_number)->GetState(); }

	bool GetButtonState(int button_num) { return PadState().Buttons[button_num - GamePad_Button1]; }


	float GetPadStateX() { return PadState().X / move_value_constant; }

	float GetPadStateY() { return PadState().Y / move_value_constant; }


	KeyboardState KeyboardState() { return Keyboard->GetState(); }

	bool KeyboardButtonState(int button_num) { return KeyboardState().IsKeyDown(button_num); }

	bool KeyboardButtonBuffer(int button_num) { return keyboardBuffer.IsPressed(button_num); }

	static void GetKeyboardBuffer() { keyboardBuffer = Keyboard->GetBuffer(); }

private:
	int pad_number;
	int const move_value_constant = 1000;

	static KeyboardBuffer keyboardBuffer;
};