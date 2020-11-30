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