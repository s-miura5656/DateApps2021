#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	i_player_data = new IPrayerData;
}

CollisionManager::~CollisionManager()
{
	
}

bool CollisionManager::Initialize()
{
	std::string player_num = "Player_";
	
	Material mat;
	mat.Diffuse = Color(1.f, 1.f, 1.f);
	mat.Ambient = Color(1.f, 1.f, 1.f);
	mat.Specular = Color(1.f, 1.f, 1.f);

	for (int i = 0; i < 4; i++)
	{
		player_num += std::to_string(i + 1);
		CreateHitBox(player_num);
		collisions[player_num]->Initialize();
		collisions[player_num]->SetHitBoxMaterial(mat);
		collisions[player_num]->SetHitBoxPos(i_player_data->GetPosition(player_num));
		collisions[player_num]->SetHitBoxSize(Vector3_One);
	}


	return true;
}

int CollisionManager::Update()
{
	std::string player_num = "Player_";

	for (int i = 0; i < 4; i++)
	{
		player_num += std::to_string(i + 1);

		collisions[player_num]->SetHitBoxPos(i_player_data->GetPosition(player_num));
	}
	return 0;
}

void CollisionManager::Draw2D()
{
}

void CollisionManager::Draw3D()
{
	std::string player_num = "Player_";

	for (int i = 0; i < 4; i++)
	{
		player_num += std::to_string(i + 1);

		collisions[player_num]->Draw3D();
	}
}

void CollisionManager::CreateHitBox(std::string& collision_name)
{
	collisions.emplace(collision_name, new Collision);
}
