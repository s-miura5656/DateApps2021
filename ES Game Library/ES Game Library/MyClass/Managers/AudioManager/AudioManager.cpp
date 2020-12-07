#include"AudioManager.h"
#include"../ResouceManager/ResouceManager.h"
AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}
bool AudioManager::Initialize()
{
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/se.wav"),_punch,MAX_PLAY,false);
	_mainbgm = ResouceManager::Instance().LordMusicFile(_T(""));
	return true;
}
void AudioManager::PunchPlay()
{
	for (auto& sound : _punch)
	{
		if (!sound->IsPlaying())
		{
			sound->Play();
		}
	}
}
void AudioManager::MainBgmPlay()
{
	_mainbgm->Play();
}