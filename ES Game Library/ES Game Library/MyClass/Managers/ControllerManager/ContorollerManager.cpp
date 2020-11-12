#include "ContorollerManager.h"

void ControllerManager::Initialize() 
{
	InputDevice.CreateGamePad(PLAYER_MAX);
}

void ControllerManager::Update() 
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		pad_state[i] = GamePad(i)->GetState();
		pad_buffer[i] = GamePad(i)->GetBuffer();
	}
}
