#include "ResouceManager.h"

SPRITE ResouceManager::LordSpriteFile(LPCTSTR sprite_file_name)
{
	auto&& it = _resouces_sprite.find(sprite_file_name);
	if (it != _resouces_sprite.end())
	{
		return it->second;
	}
	else
	{
		SPRITE sprite = GraphicsDevice.CreateSpriteFromFile(sprite_file_name);
		_resouces_sprite.emplace(sprite_file_name, sprite);
		return _resouces_sprite[sprite_file_name];
	}
}
MODEL ResouceManager::LoadModelFile(LPCTSTR model_file_name)
{
	auto&& it = _resouces_model.find(model_file_name);
	if (it != _resouces_model.end())
	{
		return it->second;
	}
	else
	{
		MODEL model = GraphicsDevice.CreateModelFromFile(model_file_name);
		_resouces_model.emplace(model_file_name, model);
		return _resouces_model[model_file_name];
	}
}
ANIMATIONMODEL ResouceManager::LoadAnimationModelFile(LPCTSTR animation_model_name)
{
	auto&& it = _resouces_animation_model.find(animation_model_name);
	if (it != _resouces_animation_model.end())
	{
		return it->second;
	}
	else
	{
		ANIMATIONMODEL animationmodel = GraphicsDevice.CreateAnimationModelFromFile(animation_model_name);
		_resouces_animation_model.emplace(animation_model_name, animationmodel);
		return _resouces_animation_model[animation_model_name];
	}
}
FONT ResouceManager::LordFontFile(LPCTSTR font_file_name,float size)
{
	auto&& it = _resouces_font.find(font_file_name);
	if (it != _resouces_font.end())
	{
		return it->second;
	}
	else
	{
		FONT font = GraphicsDevice.CreateSpriteFont(font_file_name, size);
		_resouces_font.emplace(font_file_name, font);
		return _resouces_font[font_file_name];
	}
}
SHADER ResouceManager::LordShaderFile(LPCTSTR shader_file_name)
{
	auto&& it = _resouces_shader.find(shader_file_name);
	if (it != _resouces_shader.end())
	{
		return it->second;
	}
	else
	{
		SHADER shader = GraphicsDevice.CreateEffectFromFile(shader_file_name);
		_resouces_shader.emplace(shader_file_name, shader);
		return _resouces_shader[shader_file_name];
	}
}
EFFECT ResouceManager::LordEffectFile(LPCTSTR effect_file_name)
{
	auto&& it = _resouces_effect.find(effect_file_name);
	if (it != _resouces_effect.end())
	{
		return it->second;
	}
	else
	{
		EFFECT effect = GraphicsDevice.CreateEffectFromFile(effect_file_name);
		_resouces_effect.emplace(effect_file_name, effect);
		return _resouces_effect[effect_file_name];
	}
}
SOUND ResouceManager::LordSoundFile(LPTSTR sound_file_name)
{
	auto&& it = _resouces_sound.find(sound_file_name);
	if (it != _resouces_sound.end())
	{
		return it->second;
	}
	else
	{
		SOUND sound = SoundDevice.CreateSoundFromFile(sound_file_name);
		_resouces_sound.emplace(sound_file_name, sound);
		return _resouces_sound[sound_file_name];
	}
}
MUSIC ResouceManager::LordMusicFile(LPTSTR music_file_name)
{
	auto&& it = _resouces_music.find(music_file_name);
	if (it != _resouces_music.end())
	{
		return it->second;
	}
	else
	{
		MUSIC music = SoundDevice.CreateMusicFromFile(music_file_name);
		_resouces_music.emplace(music_file_name, music);
		return _resouces_music[music_file_name];
	}
}
MEDIA ResouceManager::LordMediaFile(LPTSTR media_file_name)
{
	auto&& it = _resouces_media.find(media_file_name);
	if (it != _resouces_media.end())
	{
		return it->second;
	}
	else
	{
		MEDIA media = MediaManager.CreateMediaFromFile(media_file_name);
		_resouces_media.emplace(media_file_name, media);
		return _resouces_media[media_file_name];
	}
}