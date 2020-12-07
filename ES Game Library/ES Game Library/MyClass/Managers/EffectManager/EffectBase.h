#pragma once
#include "../../../ESGLib.h"

class EffectBase
{
public:
	EffectBase();
	~EffectBase();

	bool Initialize(LPCTSTR file);
	int EffectPlay(Vector3 pos);
	int EffectStop(int num);
	int SetScale(int num, float scale);
	int SetSpeed(int num, float speed);

	EFFEKSEER GetEffect() { return effect; }

private:
	EFFEKSEER effect;
};
