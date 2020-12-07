#pragma once
#include"../../../ESGLib.h"
class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	bool Initialize();
	enum{ MAX_PLAY = 4};
	MUSIC _mainbgm;
	void PunchPlay();
private:
	SOUND _punch[MAX_PLAY];
};