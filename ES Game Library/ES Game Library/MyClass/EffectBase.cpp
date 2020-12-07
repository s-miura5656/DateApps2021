#include "EffectBase.h"

EffectBase::EffectBase()
{

};

EffectBase::~EffectBase() 
{

};

bool EffectBase::Initialize(LPCTSTR file){
	effect = Effekseer.CreateEffectFromFile(file);
	return 0;
}

int EffectBase::EffectPlay(Vector3 pos){
	return effect->Play(pos);
}

int EffectBase::EffectStop(int num){
	effect->Stop(num);
	return 0;
}

int EffectBase::SetScale(int num,float scale) {
	effect->SetScale(num, scale);
	return 0;
}

int EffectBase::SetSpeed(int num, float speed) {
	effect->SetSpeed(num,speed);
	return 0;
}