#pragma once

#include"../../../../ESGLib.h"
#include"../../StageBase.h"
#include"../../../Item/ItemCounter/ItemCounter.h"
#include"../../../Data/WordsTable.h"

class ParticleSystem;

class Blinking
{
public:
	Blinking();
	~Blinking();
	bool Initialize(Vector3 pos);
	int Update();
	void Draw3D();
private:
	Vector3 _position;
	MODEL   _model;
	float   _scale;
};