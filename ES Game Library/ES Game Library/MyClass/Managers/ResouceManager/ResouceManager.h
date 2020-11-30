//! @file   ResouceManager.h
//! @brief  ファイル読み込みを管理しているクラス
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

	SPRITE LordSpriteFile(LPCTSTR sprite_file_name);
	MODEL LoadModelFile(LPCTSTR model_file_name);
	ANIMATIONMODEL AnimationLoadModelFile(LPCTSTR animation_model_name);
private:
	ResouceManager(const ResouceManager&) = delete;
	void operator=(const ResouceManager&) = delete;

	std::map<tstring, SPRITE> _resouces_sprite;
	std::map<tstring, MODEL> _resouces_model;
	std::map<tstring, ANIMATIONMODEL> _resouces_animation_model;
};
