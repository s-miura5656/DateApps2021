//! @file   ResouceManager.h
//! @brief  �t�@�C���ǂݍ��݂��Ǘ����Ă���N���X
//! @author Souta_Miura
//! @date   2020/11/26
#pragma once

#include "../../../ESGLib.h"
#include "../ManagerBase.h"

class ResouceManager
{
public:
	ResouceManager() {};
	~ResouceManager() {};

	static ResouceManager& Instance() {
		static ResouceManager instance;
		return instance;
	};

	MODEL LoadModelFile(LPCTSTR file_name);
	ANIMATIONMODEL AnimationLoadModelFile(std::string animfile_name);
private:
	ResouceManager(const ResouceManager&) = delete;
	void operator=(const ResouceManager&) = delete;

	std::map<LPCTSTR, MODEL> _resouces_model;
	std::map<std::string, ANIMATIONMODEL> _resouces_animation_model;
};
