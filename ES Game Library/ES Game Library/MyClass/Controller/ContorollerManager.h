#pragma once

#include"../../ESGLib.h"
#include "../../MyClass/Enum/Enum.h"

class ControllerManager
{
public:
	ControllerManager();
	~ControllerManager();

	static ControllerManager & Instance() {
		static ControllerManager instance;
		return instance;
	}

	void Initialize();
	void Update();

	GamePadState PadState() { return *pad_state; }
	GamePadBuffer PadBuffer() { return *pad_buffer; }
	

protected:
	GamePadState  pad_state[PLAYER_MAX];
	GamePadBuffer pad_buffer[PLAYER_MAX];


};
