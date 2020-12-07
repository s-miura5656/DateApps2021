#pragma once
#include"../../../ESGLib.h"
class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	bool Initialize();
	enum{ MAX_PLAY = 4};
	void PunchPlay();
	void MainBgmPlay();
private:
	SOUND _punch[MAX_PLAY];
	MUSIC _mainbgm;
};