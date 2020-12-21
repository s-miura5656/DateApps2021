#include "Time.h"

TimeManager::TimeManager()
{

}

TimeManager::~TimeManager()
{

}


void TimeManager::Initialize()
{
	limitTime  = 3.9f;
	time       = 0.0f;

	startTime  = 180.0f;
	countTime  = 3;

	startFlag = false;
}
 

void TimeManager::Update()
{
	if (startFlag == true) {
		if (time < limitTime - 0.9f)
		{
			time += (float)GameTimer.GetElapsedSecond();
		}
	}
	startTime--;
	if (startTime == 120) {
		countTime = 2;
	}
	if (startTime == 60) {
		countTime = 1;
	}
	if (startTime == 0) {
		countTime = 0;
	}
	if (startTime == -60) {
		countTime = -1;
		startTime = -60;
	}

	if (countTime == -1) {
		startFlag = true;
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

int  TimeManager::Countdown()
{
	return countTime;
}

float TimeManager::GetstartTime()
{
	return startTime;
}

bool TimeManager::StartFlag()
{ 
	return 	startFlag;
}


