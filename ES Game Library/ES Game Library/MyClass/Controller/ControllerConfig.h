#pragma once

#include"../../ESGLib.h"

class Controller
{
public:
	Controller(int number) 
	{
		_pad_number = number; 
	}

	~Controller() {}

	bool Initialize();
	void Update() {};

	void GamePadRefresh();

	bool GetButtonBuffer(int button_num) { return _pad_buffer.IsPressed(button_num); }

	bool GetButtonState(int button_num) { return _pad_state.Buttons[button_num - GamePad_Button1]; }

	float GetPadStateX() { return _pad_state.X / move_value_constant; }

	float GetPadStateY() { return _pad_state.Y / move_value_constant; }

private:
	int _pad_number;
	int const move_value_constant = 1000;
	GamePadBuffer _pad_buffer;
	GamePadState  _pad_state;
};