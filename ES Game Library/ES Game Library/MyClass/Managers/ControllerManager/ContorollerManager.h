#pragma once

#include"../../../ESGLib.h"
#include "../../Data/WordsTable.h"
#include "../../Controller/ControllerConfig.h"
//#include "../../GamePad.h"

class ControllerManager
{
public:
	ControllerManager() {}
	
	~ControllerManager();

	static ControllerManager& Instance() {
		static ControllerManager instance;
		return instance;
	};

	void SetGamePadMaxCount(int pad_count);
	void CreateGamePad(std::string player_tag);
	Controller* GetController(std::string player_tag);
	//XGamePad* GetPad() { return _game_pad; }

private:
	ControllerManager(const ControllerManager&) = delete;
	void operator=(const ControllerManager&) = delete;

	std::map<std::string, Controller*> _controller;
	//XGamePad* _game_pad;
};
