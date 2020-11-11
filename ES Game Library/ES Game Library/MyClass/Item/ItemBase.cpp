#include "Itembase.hpp"

bool ItemBase::Initialize()
{
	return true;
}

void ItemBase::Update()
{
	
}

void ItemBase::Draw2D()
{

}

void ItemBase::Draw3D()
{
	sphere->SetPosition(position);
	sphere->Draw();
}

void ItemBase::SphereShape()
{
	SimpleShape shape_sphere;

	shape_sphere.Type = Shape_Sphere;

	shape_sphere.Radius = 0.5f;
	shape_sphere.Slices = 10;
	shape_sphere.Stacks = 10;

	sphere = GraphicsDevice.CreateModelFromSimpleShape(shape_sphere);
}
