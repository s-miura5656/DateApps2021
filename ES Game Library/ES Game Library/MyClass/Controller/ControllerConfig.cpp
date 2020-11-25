#include"ControllerConfig.h"

::KeyboardBuffer Controller::keyboardBuffer;


bool Controller::Initialize()
{
	return true;
}

void  Controller::Update()
{

}

GamePadBuffer Controller::PadBuffer()
{
	auto&& buffer = GamePad(pad_number)->GetBuffer();

	return buffer;
}

GamePadState Controller::PadState()
{
	auto&& state = GamePad(pad_number)->GetState();
	
	return state;
}
