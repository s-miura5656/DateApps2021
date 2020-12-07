#pragma once
#include "../ESGLib.h"

class EffectBase
{
public:
	EffectBase();
	~EffectBase();

	virtual bool Initialize(LPCTSTR file);
	virtual int EffectPlay(Vector3 pos);
	virtual int EffectStop(int num);
	virtual int SetScale(int num, float scale);
	virtual int SetSpeed(int num, float speed);

	EFFEKSEER GetEffect() { return effect; }

private:
	EFFEKSEER effect;

};
