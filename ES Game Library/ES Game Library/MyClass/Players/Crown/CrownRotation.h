#include"../../../ESGLib.h"

class CrownRotation
{
public:

	bool Initialize();
	int Update();
	void Draw3D();

private:

	MODEL _model;
	EFFEKSEER _effect;

	MODEL mikoto;
	float time;
};