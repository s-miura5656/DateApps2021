#include "EffectBase.h"

EffectBase::EffectBase()
{

};

EffectBase::~EffectBase() 
{
	delete effect;
};

bool EffectBase::Initialize(LPCTSTR file){
	effect = Effekseer.CreateEffectFromFile(file);
	_is_playing = false;
	return 0;
}

int EffectBase::EffectPlay(Vector3 pos){
	_is_playing = true;
	return effect->Play(pos);
}

void EffectBase::EffectStop(int num){
	_is_playing = false;
	effect->Stop(num);
}

void EffectBase::SetPosition(int track, Vector3 position)
{
	effect->SetPosition(track, position);
}

void EffectBase::SetScale(int num,float scale) 
{
	effect->SetScale(num, scale);
}

void EffectBase::SetSpeed(int num, float speed) 
{
	effect->SetSpeed(num,speed);
}