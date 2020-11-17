#pragma once

#include"../../../ESGLib.h"
#include "../../Data/WordsTable.h"
#include "../../Controller/ControllerConfig.h"

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

private:
	ControllerManager(const ControllerManager&) = delete;
	void operator=(const ControllerManager&) = delete;

	std::map<std::string, Controller*> controller;

};
