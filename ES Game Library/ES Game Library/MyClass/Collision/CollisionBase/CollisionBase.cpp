#include "../CollisionBase/CollisionBase.h"

CollisionBase::CollisionBase()
{
	SimpleShape shape;

	shape.Type = Shape_Box;
	shape.Depth = 1;
	shape.Height = 1;
	shape.Width = 1;

	hitbox = GraphicsDevice.CreateModelFromSimpleShape(shape);
}

CollisionBase::~CollisionBase()
{
}

void CollisionBase::Initialize()
{

	//Material material;
	//material.Diffuse = Color(1.0f, .0f, 1.0f);
	//material.Ambient = Color(0.5f, 0.5f, 0.5f);
	//material.Specular = Color(1.0f, 1.0f, 1.0f);
	//material.Power = 10.0f;

	//四角形を作る

	
	//マテリアルで色つけてplayerの場所にセットする
	//hitbox->SetMaterial(material);

	//	攻撃判定

	//shape.Type = Shape_Box;
	//shape.Depth = 30;
	//shape.Height = 10;
	//shape.Width = 6;
	//attack_box = GraphicsDevice.CreateModelFromSimpleShape(shape);
	//attack_box->SetMaterial(material);
	//attack_switch = false;


	////ブロックの当たり判定

	//shape.Type = Shape_Box;
	//shape.Depth = 40;
	//shape.Height = 40;
	//shape.Width = 40;
	//block_box = GraphicsDevice.CreateModelFromSimpleShape(shape);
	//block_box->SetPosition(block->GetPosition());
	//block_box->SetMaterial(material);

	//block->SetScale(0.0254);
	////アイテム
	//shape.Type = Shape_Box;
	//shape.Depth = 15;
	//shape.Height = 15;
	//shape.Width = 15;
	//Stone_box = GraphicsDevice.CreateModelFromSimpleShape(shape);

	//Stone_box->SetMaterial(material);
}

void CollisionBase::Update()
{
	//OrientedBoundingBox robo_hitbox = hitbox->GetOBB();
	//OrientedBoundingBox robo_attack_box = attack_box->GetOBB();
	//OrientedBoundingBox block_hitbox = block_box->GetOBB();
	//OrientedBoundingBox Stone_hitbox = Stone_box->GetOBB();
}

void CollisionBase::Draw3D()
{
	//hitbox->Draw();
}