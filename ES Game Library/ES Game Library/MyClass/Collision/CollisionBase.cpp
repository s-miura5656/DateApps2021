//! @file   CollisionBase.h
//! @brief  “–‚½‚è”»’è—p‚ÌŠî’êƒNƒ‰ƒX
//! @author Souta_Miura
//! @date   2020/11/05

#include "../Collision/CollisionBase.h"

CollisionBase::CollisionBase()
{
	SimpleShape shape;

	shape.Type = Shape_Box;
	shape.Depth = 1;
	shape.Height = 1;
	shape.Width = 1;

	box = GraphicsDevice.CreateModelFromSimpleShape(shape);
}

CollisionBase::~CollisionBase()
{

}

bool CollisionBase::Initialize()
{
	return true;
}


void CollisionBase::Draw3D()
{
#ifdef DEBUG
	GraphicsDevice.BeginAlphaBlend();
	box->DrawAlpha(0.5f);
	GraphicsDevice.EndAlphaBlend();
#endif
}