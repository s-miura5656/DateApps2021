#include "ResouceManager.h"

MODEL ResouceManager::LoadModelFile(LPCTSTR file_name)
{
	auto&& it = _resouces_model.find(file_name);

	if (it != _resouces_model.end())
	{
		return it->second;
	}
	else
	{
		MODEL model = GraphicsDevice.CreateModelFromFile(file_name);

		_resouces_model.emplace(file_name, model);
		
		return _resouces_model[file_name];
	}
}
ANIMATIONMODEL ResouceManager::AnimationLoadModelFile(LPCTSTR animfile_name)
{
	auto&& it = _resouces_animation_model.find(animfile_name);

	if (it != _resouces_animation_model.end())
	{
		return it->second;
	}
	else
	{
		ANIMATIONMODEL animationmodel = GraphicsDevice.CreateAnimationModelFromFile(animfile_name);

		_resouces_animation_model.emplace(animfile_name, animationmodel);

		return _resouces_animation_model[animfile_name];
	}
}