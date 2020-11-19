#include "Time.h"

TimeManager::TimeManager()
{

}

TimeManager::~TimeManager()
{
//	timeEndPeriod(1);
}


void TimeManager::Initialize()
{
	//timeBeginPeriod(1);

	//
	//startTime = 0;
	//nowTime = 0;
	//time = 0;
	limitTime = 60.9f;
	time = 0.0f;
}
 

void TimeManager::Update()
{
	time += (float)GameTimer.GetElapsedSecond();
	//if (startTime == 0)
	//{
	//	startTime = timeGetTime();
	//}

	//nowTime = timeGetTime();




	///*
	//time_limit++;
	//if (time_limit >= 60) {

	//	real_time++;
	//	time_limit = 0;
	//}
	//*/

	//time = limitTime - ((nowTime - startTime) / 1000);
	
}


