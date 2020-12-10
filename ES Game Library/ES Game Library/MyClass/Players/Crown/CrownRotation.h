#include"../../../ESGLib.h"
#include"../../Data/IData.h"

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
	EFFEKSEER _effect;

	float time;
	IPrayerData* _i_player_data;
	Vector3 _position;
	string camp;
	string camp_2;

	int effectnum;
};