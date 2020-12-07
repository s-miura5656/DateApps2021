#pragma once

#include "../../../ESGLib.h"
#include "EffectBase.h"
#include "../../Data/WordsTable.h"
#include "../../Data/IData.h"
#include "../../Managers/ManagerBase.h"

class EffectManager : public ManagerBase
{
public:
	EffectManager();
	~EffectManager();
	
	static EffectManager& Instance() {
		static EffectManager instance;
		return instance;
	};

	bool Initialize() override { return true; }
	int Update() override { return 0; }
	void Draw2D() override {};
	void Draw3D() override {};

	void CreateEffect(std::string path, std::string file_name);
	EffectBase* GetEffect(std::string file_name) { return eb[file_name]; }
private:
	EffectManager(const EffectManager&) = delete;
	void operator=(const EffectManager&) = delete;

	std::map<std::string, EffectBase*> eb;
};
