#include "EffectManager.h"
#include "../../Data/MyAlgorithm.h"
#include "../../Data/IData.h"
#include "../../Data/WordsTable.h"

EffectManager::EffectManager() 
{

};

EffectManager::~EffectManager()
{
	
};

void EffectManager::CreateEffect(std::string path, std::string file_name)
{
	auto&& it = eb.find(file_name);

	if (it != eb.end())
	{
		
	}
	else
	{
		eb.emplace_hint(eb.end(), file_name, new EffectBase);
		auto file_path = ConvertFilePath(path, file_name, ".efk");
		eb[file_name]->Initialize(file_path.c_str());
	}
}
