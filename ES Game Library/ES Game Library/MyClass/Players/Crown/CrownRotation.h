#include"../../../ESGLib.h"
#include"../../Data/IData.h"
#include"../../Data/StructList.h"

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
	EFFECT _shader;

	Material _model_material;
	std::unique_ptr<ParticleSystem> _effect;
	IPrayerData* _i_player_data;

	Transform _transform;

	float rankingpoint_max;
	float rankingpoint_min;

	bool crown_flag;
};