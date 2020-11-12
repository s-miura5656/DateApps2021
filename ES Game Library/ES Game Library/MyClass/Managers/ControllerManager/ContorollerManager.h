#pragma once

#include"../../../ESGLib.h"
#include "../../Data/GameData.h"

using namespace PlayerEnum;

class ControllerManager
{
public:
	ControllerManager() {};
	~ControllerManager() {};

	static ControllerManager & Instance() {
		static ControllerManager instance;
		return instance;
	}

	void Initialize();
	void Update();

	GamePadState PadState() { return *pad_state; }
	GamePadBuffer PadBuffer() { return *pad_buffer; }
	

private:
	ControllerManager(const ControllerManager&) = delete;
	void operator=(const ControllerManager&) = delete;

	GamePadState  pad_state[PLAYER_MAX];
	GamePadBuffer pad_buffer[PLAYER_MAX];


};
