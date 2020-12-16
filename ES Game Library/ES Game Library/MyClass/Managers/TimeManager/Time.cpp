#include "Time.h"

TimeManager::TimeManager()
{

}

TimeManager::~TimeManager()
{

}


void TimeManager::Initialize()
{
	limitTime = 5.9f;
	time = 0.0f;
}
 

void TimeManager::Update()
{
	if (time < limitTime - 0.9f)
	{
		time += (float)GameTimer.GetElapsedSecond();
	}
}

int TimeManager::GetTimeMinutes()
{
	int ret = 0;

	ret = ((int)(GetTimeLeft()) % 3600) / 60;

	return ret;
}

int TimeManager::GetTimeSeconds()
{
	int ret = 0;

	ret = (int)( GetTimeLeft() ) % 60;

	return ret;
}


