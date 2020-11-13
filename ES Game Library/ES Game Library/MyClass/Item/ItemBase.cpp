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
	_box->SetPosition(_position);
	_box->Draw();
}

void ItemBase::SphereShape()
{
	SimpleShape shape_box;

	shape_box.Type = Shape_Box;

	shape_box.Width = 0.6;
	shape_box.Height = 0.6;
	shape_box.Depth = 0.6;

	_box = GraphicsDevice.CreateModelFromSimpleShape(shape_box);
}
