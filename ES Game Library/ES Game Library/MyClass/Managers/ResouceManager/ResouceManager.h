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
	ANIMATIONMODEL LoadAnimationModelFile(LPCTSTR animation_model_name);
	FONT LordFontFile(LPCTSTR font_file_name, float size);
	SHADER LordShaderFile(LPCTSTR shader_file_name);
	EFFECT LordEffectFile(LPCTSTR effect_file_name);
	SOUND LordSoundFile(LPTSTR sound_file_name);
	MUSIC LordMusicFile(LPTSTR music_file_name);
	MEDIA LordMediaFile(LPTSTR media_file_name);
private:
	ResouceManager(const ResouceManager&) = delete;
	void operator=(const ResouceManager&) = delete;

	std::map<tstring, SPRITE>			_resouces_sprite;
	std::map<tstring, MODEL>			_resouces_model;
	std::map<tstring, ANIMATIONMODEL>   _resouces_animation_model;
	std::map<tstring, FONT>				_resouces_font;
	std::map<tstring, SHADER>			_resouces_shader;
	std::map<tstring, EFFECT>			_resouces_effect;
	std::map<tstring, SOUND>			_resouces_sound;
	std::map<tstring, MUSIC>			_resouces_music;
	std::map<tstring, MEDIA>			_resouces_media;
};
