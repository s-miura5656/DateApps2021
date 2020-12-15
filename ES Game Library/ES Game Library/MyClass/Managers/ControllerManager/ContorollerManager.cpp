#include "ContorollerManager.h"
#include "../../Data/WordsTable.h"
#include "../../Data/MyAlgorithm.h"

ControllerManager::~ControllerManager()
{
	delete _game_pad;

	for (auto& it = _controller.rbegin(); it != _controller.rend(); ++it)
	{
		delete (*it).second;
	}
}

void ControllerManager::SetGamePadMaxCount(int pad_count)
{
	InputDevice.CreateGamePad(pad_count);
	_game_pad = new XGamePad;
}

void ControllerManager::CreateGamePad(std::string player_tag)
{
	auto pad_num = GetTagNum(player_tag);

	_controller.emplace(player_tag, new Controller(pad_num - 1));
}

Controller* ControllerManager::GetController(std::string player_tag)
{
	return _controller[player_tag];
}
