#include"../../../ESGLib.h"
#include"../../Data/IData.h"

class ParticleSystem;

class CrownRotation
{
public:
	CrownRotation();
	~CrownRotation();

	bool Initialize();
	int Update();
	void Draw3D();

private:

	MODEL _model;
	std::unique_ptr<ParticleSystem> _effect;
	IPrayerData* _i_player_data;

	Vector3 _position;
	float rankingpoint_max;
	float rankingpoint_min;

	bool crown_flag;
};