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
	InitializePlayerHitBoxs();
	InitializeArmHitBoxs();

	return true;
}

int CollisionManager::Update()
{
	UpdatePlayerHitBoxs();
	UpdateArmHitBoxs();

	for (int i = 0; i < 4; ++i)
	{
		std::string arm_num = "Arm_" + std::to_string(i + 1);

		for (int j = 0; j < 4; ++j)
		{
			std::string player_num = "Player_" + std::to_string(j + 1);

			if (i == j)
				continue;

			bool hit = collisions[arm_num]->GetBoxCollision().Intersects(collisions[player_num]->GetBoxCollision());

			collisions[player_num]->SetAttackHit(hit);

			if (collisions[player_num]->GetAttackHit())
			{
				Material hit_mat;
				hit_mat.Diffuse = Color(1.f, 0.f, 0.f);
				hit_mat.Ambient = Color(1.f, 0.f, 0.f);
				hit_mat.Specular = Color(1.f, 0.f, 0.f);

				collisions[player_num]->SetHitBoxMaterial(hit_mat);
			}
			else
			{
				Material mat;
				mat.Diffuse = Color(1.f, 1.f, 1.f);
				mat.Ambient = Color(1.f, 1.f, 1.f);
				mat.Specular = Color(1.f, 1.f, 1.f);

				//collisions[player_num]->SetHitBoxMaterial(mat);
			}
		}
	}

	return 0;
}

void CollisionManager::Draw2D()
{
}

void CollisionManager::Draw3D()
{
	DrawPlayerHitBoxs();
	DrawArmHitBoxs();
}

void CollisionManager::InitializePlayerHitBoxs()
{
	Material mat;
	mat.Diffuse = Color(1.f, 1.f, 1.f);
	mat.Ambient = Color(1.f, 1.f, 1.f);
	mat.Specular = Color(1.f, 1.f, 1.f);

	for (int i = 0; i < 4; i++)
	{
		std::string player_num = "Player_" + std::to_string(i + 1);
		CreateHitBox(player_num);
		collisions[player_num]->Initialize();
		collisions[player_num]->SetHitBoxMaterial(mat);
		collisions[player_num]->SetHitBoxPos(i_player_data->GetPosition(player_num));
		collisions[player_num]->SetHitBoxSize(Vector3_One);
	}
}

void CollisionManager::UpdatePlayerHitBoxs()
{
	for (int i = 0; i < 4; i++)
	{
		std::string player_num = "Player_" + std::to_string(i + 1);
		collisions[player_num]->SetHitBoxPos(i_player_data->GetPosition(player_num));
	}
}

void CollisionManager::DrawPlayerHitBoxs()
{
	for (int i = 0; i < 4; i++)
	{
		std::string player_num = "Player_" + std::to_string(i + 1);
		collisions[player_num]->Draw3D();
	}
}

void CollisionManager::InitializeArmHitBoxs()
{
	Material mat;
	mat.Diffuse = Color(1.f, 1.f, 1.f);
	mat.Ambient = Color(1.f, 1.f, 1.f);
	mat.Specular = Color(1.f, 1.f, 1.f);

	for (int i = 0; i < 4; i++)
	{
		std::string arm_num = "Arm_" + std::to_string(i + 1);
		CreateHitBox(arm_num);
		collisions[arm_num]->Initialize();
		collisions[arm_num]->SetHitBoxMaterial(mat);
		collisions[arm_num]->SetHitBoxPos(i_player_data->GetArmModelPos(arm_num));
		collisions[arm_num]->SetHitBoxSize(Vector3(1.f, 2.f, 1.f) * 0.5f);
	}
}

void CollisionManager::UpdateArmHitBoxs()
{
	for (int i = 0; i < 4; i++)
	{
		std::string arm_num = "Arm_" + std::to_string(i + 1);

		collisions[arm_num]->SetHitBoxPos(i_player_data->GetArmModelPos(arm_num));
	}
}

void CollisionManager::DrawArmHitBoxs()
{
	for (int i = 0; i < 4; i++)
	{
		std::string arm_num = "Arm_" + std::to_string(i + 1);

		collisions[arm_num]->Draw3D();
	}
}

void CollisionManager::CreateHitBox(std::string& collision_name)
{
	collisions.emplace(collision_name, new Collision);
}
