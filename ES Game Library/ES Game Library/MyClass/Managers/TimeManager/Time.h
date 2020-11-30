#pragma once
#include "../TimeManager/Time.h"
#include "../../../ESGLib.h"

class TimeManager
{
private:
	TimeManager(const TimeManager&) = delete;
	void operator=(const TimeManager&) = delete;



public:
	TimeManager();
    ~TimeManager();

	static TimeManager& Instance() {
		static TimeManager instance;
		return instance;
	};

	void Initialize();
	void Update();

	inline float GetLimitTime() const { return limitTime; }
	inline float GetTime()		const { return time; }
	inline float GetTimeLeft()  const { return limitTime - time; }

private:
	float limitTime;
	float time;

	//DWORD startTime;
	//DWORD nowTime;
	//DWORD time;
	//DWORD limitTime;
	};

