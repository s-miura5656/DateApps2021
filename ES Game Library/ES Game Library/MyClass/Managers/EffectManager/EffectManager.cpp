#include "EffectManager.h"
EffectManager::EffectManager() 
{
	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		player_tag = PLAYER_TAG + std::to_string(i+1);
	}
};

EffectManager::~EffectManager()
{

};

bool EffectManager::Initialize() 
{
	eb[EffectEnum::PUNCH].Initialize(_T("Effect/effect_flash/flash.efk"));
	return 0;
}

int EffectManager::Update() 
{
	Effekseer.Update();

	auto player_pos = _i_player_data.GetPosition(player_tag);
	auto effect_num = eb[EffectEnum::PUNCH].EffectPlay(Vector3(2, 1, -1));
	eb[EffectEnum::PUNCH].SetSpeed(effect_num, 1.f);
	eb[EffectEnum::PUNCH].SetScale(effect_num, 0.3f);

	return 0;
}

void EffectManager::Draw2D()
{

}

void EffectManager::Draw3D()
{
	Effekseer.Draw();
}