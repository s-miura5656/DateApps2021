#pragma once

#include "../../../ESGLib.h"
#include "../../Data/StructList.h"

class ArmParametor
{
public:
	friend class IPrayerData;

	ArmParametor() {}
	~ArmParametor() {};

	static ArmParametor& Instance() {
		static ArmParametor instance;
		return instance;
	};

	void CreateParametor(std::string name) { _arm_params.emplace(name, _arm_param); }
private:
	ArmParametor(const ArmParametor&) = delete;
	void operator=(const ArmParametor&) = delete;

	std::map<std::string, ArmParam> _arm_params;
	ArmParam _arm_param;

};