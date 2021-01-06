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
	Matrix rotation = Matrix_CreateFromYawPitchRoll(0.0f, 45.0f, 45.0f);
	rotation *= Matrix_CreateRotationY(_rotation);
	_box->SetDirection(Quaternion_CreateFromRotationMatrix(rotation));
	_box->SetPosition(_position);
	_hit_box->SetHitBoxPosition(_position);
	_box->Draw();
}

void ItemBase::BoxShape(int scale)
{
	if (scale >= 5) {
		scale = 5;
	}
	SimpleShape shape_box{};

	shape_box.Type = Shape_Box;

	shape_box.Width = 0.2  * scale;
	shape_box.Height = 0.2 * scale;
	shape_box.Depth = 0.2 * scale;

	_box = GraphicsDevice.CreateModelFromSimpleShape(shape_box);
}

void ItemBase::RotationItem()
{
	_rotation += 1.0f;
	if (_rotation >= 360.0f)
		_rotation -= 360.0f;
}
