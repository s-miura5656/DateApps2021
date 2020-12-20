#pragma once

#include "../../../ESGLib.h"
#include "../../Data/StructList.h"
#include "../../Data/IData.h"

class Wire
{
public:
	Wire(std::string arm_tag);
	~Wire();

	bool Initialize();
	int  Update();
	void Draw2D() {};
	void Draw3D();
private:
	//! file
	MODEL  _model;
	EFFECT _shader;
	SPRITE _texture;

	//! transform
	Transform _transform;

	//! material
	Material _material;

	//! tag
	std::string _arm_tag;

	//! pointer
	std::unique_ptr<IArmData> _i_arm_data;
};
