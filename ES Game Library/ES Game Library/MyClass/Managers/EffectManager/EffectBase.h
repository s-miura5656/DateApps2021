#pragma once
#include "../../../ESGLib.h"

class EffectBase
{
public:
	EffectBase();
	~EffectBase();

	bool Initialize(LPCTSTR file);
	int EffectPlay(Vector3 pos);
	void EffectStop(int track);
    void SetPosition(int track, Vector3 position);
    void SetScale(int track, float scale);
    void SetSpeed(int track, float speed);

	bool IsPlaying() const { return _is_playing; }

	EFFEKSEER GetEffect() { return effect; }

private:
	EFFEKSEER effect;
	bool _is_playing;
};
