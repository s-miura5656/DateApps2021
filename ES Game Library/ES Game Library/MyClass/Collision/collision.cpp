#include "../Collision/Collision.h"

Collision::Collision()
{

}

Collision::~Collision()
{

}

bool Collision::Initialize()
{
	SimpleShape shape_box;

	shape_box.Type = Shape_Box;
	shape_box.Depth = 1;
	shape_box.Height = 1;
	shape_box.Width = 1;

	box = GraphicsDevice.CreateModelFromSimpleShape(shape_box);

	return true;
}
