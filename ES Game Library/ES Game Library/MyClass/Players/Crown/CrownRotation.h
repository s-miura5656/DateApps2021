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

	//! file
	MODEL _model;
	EFFECT _shader;

	//! material
	Material _model_material;

	//! pointer
	std::unique_ptr<ParticleSystem> _effect;
	IPrayerData* _i_player_data;

	//! position
	Vector3 _position;

	//! 
	float rankingpoint_max;
	float rankingpoint_min;

	//! flag
	bool crown_flag;
};