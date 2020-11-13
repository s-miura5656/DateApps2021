#include "ContorollerManager.h"
#include "../../Data/GameData.h"


ControllerManager::~ControllerManager()
{
	for (auto& it = controller.rbegin(); it != controller.rend(); ++it)
	{
		delete (*it).second;
	}
}

void ControllerManager::SetGamePadMaxCount(int pad_count)
{
	InputDevice.CreateGamePad(pad_count);
}

void ControllerManager::CreateGamePad(std::string player_tag)
{
	auto pad_num = GetTagNum(player_tag);

	controller.emplace(player_tag, new Controller(pad_num - 1));
}

Controller* ControllerManager::GetController(std::string player_tag)
{
	return controller[player_tag];
}
