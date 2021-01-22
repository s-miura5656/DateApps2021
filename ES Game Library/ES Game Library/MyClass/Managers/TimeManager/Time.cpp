#include "Time.h"

TimeManager::TimeManager()
{

}

TimeManager::~TimeManager()
{

}

void TimeManager::Initialize()
{
	limitTime  = 40.9f;
	time       = 0.0f;

	startTime  = 181.0f;
	countTime  = 3;

	startFlag = false;

	game_end = false;

	transition_time = 0;
}
 

void TimeManager::Update()
{

	if (startFlag == true) {
		if (time < limitTime - 0.9f)
		{
			time += (float)GameTimer.GetElapsedSecond();
		}
	}
	
	if (GetTimeLeft() <= 1) {
		game_end = true;
		if (game_end == true)
		{
			transition_time += (float)GameTimer.GetElapsedSecond();
		}
	}

	startTime--;
	
	if (startTime == 180) {
		countTime = 3;
	}
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

//! @fn 制限時間（分）
//! @return 制限時間を分で返す
int TimeManager::GetTimeMinutes()
{
	int ret = 0;

	ret = ((int)(GetTimeLeft()) % 3600) / 60;

	return ret;
}

//! @fn 制限時間（秒）
//! @return 制限時間を秒で返す
int TimeManager::GetTimeSeconds()
{
	int ret = 0;

	ret = (int)( GetTimeLeft() ) % 60;

	return ret;
}

int TimeManager::GetTimeTensPlace()
{
	int ret = 0;

	ret = (int)(GetTimeLeft()) % 60 / 10;

	return ret;
}

int TimeManager::GetTimeOnesPlace()
{
	int ret = 0;

	ret = (int)(GetTimeLeft()) % 60 % 10;

	return ret;
}

//! @fn カウントダウン
//! @return カウントダウンの秒を返す
int  TimeManager::Countdown()
{
	return countTime;
}

//! @fn カウントダウン
//! @return カウントダウンをfloatで返す
float TimeManager::GetStartTime()
{
	return startTime;
}

//! @fn ゲームが始まっているかどうか
//! @return ゲームがスタートしていればtrue,スタートしていなければfalse
//! @detail ゲームがスタートして制限時間を計測しているかどうか
bool TimeManager::StartFlag()
{ 
	return 	startFlag;
}



