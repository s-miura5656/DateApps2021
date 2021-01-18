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
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/punchshot.wav"),_punchshot,MAX_PLAY,false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/indestructible.wav"), _indestructible, MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/destruction.wav"), _destruction, MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/mapgimmick.wav"), _mapgimmick, MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/pointaddition.wav"), _pointaddition, MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/explosion.wav"), _explosion, MAX_PLAY, false);
	_mainbgm = ResouceManager::Instance().LordMusicFile(_T("Audio/Bgm/MainBgm.wav"));
	return true;
}
void AudioManager::PunchShotPlay()
{
	for (auto& sound : _punchshot)
	{
		if (!sound->IsPlaying())
		{
			sound->Play();
			break;
		}
	}
}
void AudioManager::IndestructiblePlay()
{
	for (auto& sound : _indestructible)
	{
		if (!sound->IsPlaying())
		{
			sound->Play();
			break;
		}
	}
}
void AudioManager::DestructionPlay()
{
	for (auto& sound : _destruction)
	{
		if (!sound->IsPlaying())
		{
			sound->Play();
			break;
		}
	}
}
void AudioManager::MapGimmickPlay()
{
	for (auto& sound : _mapgimmick)
	{
		if (!sound->IsPlaying())
		{
			sound->Play();
			break;
		}
	}
}
void AudioManager::PointAddition()
{
	for (auto& sound : _pointaddition)
	{
		if (!sound->IsPlaying())
		{
			sound->Play();
			break;
		}
	}
}
void AudioManager::ExplosionPlay()
{
	for (auto& sound : _explosion)
	{
		if (!sound->IsPlaying())
		{
			sound->Play();
			break;
		}
	}
}
void AudioManager::MainBgmPlay()
{
	if(!_mainbgm->IsPlaying())
	_mainbgm->Play();
}