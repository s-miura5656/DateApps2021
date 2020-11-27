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
