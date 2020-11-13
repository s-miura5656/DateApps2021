#include "Itembase.hpp"

bool ItemBase::Initialize()
{
	return true;
}

int ItemBase::Update()
{
	return 0;
}

void ItemBase::Draw2D()
{

}

void ItemBase::Draw3D()
{
	_hit_box->SetHitBoxPosition(_position);
	_sphere->SetPosition(_position);
	_sphere->Draw();
}

void ItemBase::SphereShape()
{
	SimpleShape shape_sphere;

	shape_sphere.Type = Shape_Sphere;

	shape_sphere.Radius = 0.5f;
	shape_sphere.Slices = 10;
	shape_sphere.Stacks = 10;

	_sphere = GraphicsDevice.CreateModelFromSimpleShape(shape_sphere);
}
