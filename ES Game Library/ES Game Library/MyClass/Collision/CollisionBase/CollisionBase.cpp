#include "../CollisionBase/CollisionBase.h"

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

void CollisionBase::Initialize()
{
	
}


void CollisionBase::Draw3D()
{
#ifdef DEBUG
	GraphicsDevice.BeginAlphaBlend();
	box->DrawAlpha(0.5f);
	GraphicsDevice.EndAlphaBlend();
#endif
}