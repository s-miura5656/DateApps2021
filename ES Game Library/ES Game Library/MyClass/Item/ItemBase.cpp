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
	//_box->SetDirection(Quaternion_CreateFromRotationMatrix(rotation));
	//_box->SetPosition(_position);
	_model->SetScale(_scale);
	_model->SetPosition(_position + Vector3(0, 0.5, 0));
	_model->SetRotation(Vector3(30, 0, 0));
	_model->Rotation(Vector3(0, -_rotation, 0));
	_model->Draw();
	_hit_box->SetHitBoxPosition(_position);
	//_box->Draw();
}

void ItemBase::BoxShape(int scale)
{
	if (scale >= 4) {
		scale = 4;
	}
	SimpleShape shape_box{};

	shape_box.Type = Shape_Box;

	shape_box.Width = 0.3  * scale;
	shape_box.Height = 0.3 * scale;
	shape_box.Depth = 0.3 * scale;

	//_box = GraphicsDevice.CreateModelFromSimpleShape(shape_box);
}

void ItemBase::RotationItem()
{
	_rotation += 1.0f;
	if (_rotation >= 360.0f)
		_rotation -= 360.0f;
}
ITEMEFFECT ItemBase::GetEffect()
{
	ITEMEFFECT effect;
	effect._effect_time = _effect_time;
	effect._player_speed = _player_speed;
	effect._arm_speed = _arm_speed;

	return effect;
}