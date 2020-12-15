//--------------------------------------------------------------------------------------
// File: GamePad.cpp
//--------------------------------------------------------------------------------------
#define NOMINMAX

#include "GamePad.h"
#include <XInput.h>

#pragma comment(lib,"xinput9_1_0.lib")

XGamePad::XGamePad()
{
	XInputEnable(true);
}

XGamePad::State GetState(const DWORD index)
{
	XINPUT_STATE xstate;
	const auto result = XInputGetState(index, &xstate);

	XGamePad::State state;

	state.connected = (result != 0);
	if (state.connected == 0) {
		state.buttons.a			 = false;
		state.buttons.b			 = false;
		state.buttons.x			 = false;
		state.buttons.y			 = false;
		state.buttons.start		 = false;
		state.buttons.back		 = false;
		state.triggers.left		 = 0.0f;
		state.triggers.right	 = 0.0f;
		state.thumbSticks.leftX  = 0.0f;
		state.thumbSticks.leftY  = 0.0f;
		state.thumbSticks.rightX = 0.0f;
		state.thumbSticks.rightY = 0.0f;
		return;
	}

	state.buttons.a			 = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_A)	    != 0;
	state.buttons.b			 = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_B)	    != 0;
	state.buttons.x			 = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_X)	    != 0;
	state.buttons.y			 = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_Y)	    != 0;
	state.buttons.start		 = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_START) != 0;
	state.buttons.back		 = (xstate.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)  != 0;
	state.triggers.left		 = xstate.Gamepad.bLeftTrigger;
	state.triggers.right	 = xstate.Gamepad.bRightTrigger;

	state.thumbSticks.leftX  = xstate.Gamepad.sThumbLX;
	state.thumbSticks.leftY  = xstate.Gamepad.sThumbLY;

	state.thumbSticks.rightX = xstate.Gamepad.sThumbRX;
	state.thumbSticks.rightY = xstate.Gamepad.sThumbRY;

	return state;
}