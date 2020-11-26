#include"ControllerConfig.h"

bool Controller::Initialize()
{
	return true;
}

void Controller::GamePadRefresh()
{
	_pad_buffer = GamePad(_pad_number)->GetBuffer();
	_pad_state  = GamePad(_pad_number)->GetState();
}


