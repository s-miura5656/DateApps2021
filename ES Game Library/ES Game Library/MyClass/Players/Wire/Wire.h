#pragma once

#include "../../../ESGLib.h"
#include "../../Data/StructList.h"
#include "../../Data/IData.h"
#include "../../ParticleSystem/Particle.h"

class Wire
{
public:
	Wire(Transform arm_transform);
	~Wire();

	bool Initialize();
	int  Update() {};
	void Draw2D() {};
	void Draw3D();

	void SetTransForm(Transform transform) { _transform = transform; }

private:
	//! pointer
	std::unique_ptr<ParticleSystem> _effect;

	//! transform
	Transform _transform;

	//! material
	Material _material;
};
