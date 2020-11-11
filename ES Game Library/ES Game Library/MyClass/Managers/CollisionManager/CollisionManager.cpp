#include "CollisionManager.h"
#include "../../Data/GameData.h"

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
	UpdateHitBoxs(PLAYER_TAG, PLAYER_COUNT_MAX);
	UpdateHitBoxs(ARM_TAG, PLAYER_COUNT_MAX);

	UpdateArmHitBoxs();

	return 0;
}

void CollisionManager::Draw2D()
{
}

void CollisionManager::Draw3D()
{
	DrawHitBoxs(PLAYER_TAG, PLAYER_COUNT_MAX);
	DrawHitBoxs(ARM_TAG, PLAYER_COUNT_MAX);
}

void CollisionManager::InitializePlayerHitBoxs()
{
	Material mat;
	mat.Diffuse = Color(1.f, 1.f, 1.f);
	mat.Ambient = Color(1.f, 1.f, 1.f);
	mat.Specular = Color(1.f, 1.f, 1.f);

	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		std::string player_num = PLAYER_TAG + std::to_string(i + 1);
		CreateHitBox(player_num);
		collisions[player_num]->Initialize();
		collisions[player_num]->SetHitBoxMaterial(mat);
		collisions[player_num]->SetHitBoxPos(i_player_data->GetPosition(player_num));
		collisions[player_num]->SetHitBoxSize(Vector3_One);
	}
}

void CollisionManager::UpdateHitBoxs(std::string tag, int max_loop_count)
{
	for (int i = 0; i < max_loop_count; ++i)
	{
		std::string num = tag + std::to_string(i + 1);
		collisions[num]->SetHitBoxPos(i_player_data->GetPosition(num));
	}
}

void CollisionManager::DrawHitBoxs(std::string tag, int max_loop_count)
{
	for (int i = 0; i < max_loop_count; ++i)
	{
		std::string num = tag + std::to_string(i + 1);
		collisions[num]->Draw3D();
	}
}

void CollisionManager::InitializeArmHitBoxs()
{
	Material mat;
	mat.Diffuse = Color(1.f, 1.f, 1.f);
	mat.Ambient = Color(1.f, 1.f, 1.f);
	mat.Specular = Color(1.f, 1.f, 1.f);

	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		std::string arm_num = ARM_TAG + std::to_string(i + 1);
		CreateHitBox(arm_num);
		collisions[arm_num]->Initialize();
		collisions[arm_num]->SetHitBoxMaterial(mat);
		collisions[arm_num]->SetHitBoxPos(i_player_data->GetArmModelPos(arm_num));
		collisions[arm_num]->SetHitBoxSize(Vector3(1.f, 2.f, 1.f) * 0.5f);
	}
}

void CollisionManager::UpdateArmHitBoxs()
{
	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		//! 判定初期化
		std::string player_num = PLAYER_TAG + std::to_string(i + 1);
		bool reset = false;

		//! ヒット状態をリセット
		if (collisions[player_num]->GetAttackHit())
			collisions[player_num]->SetAttackHit(reset);
	}

	for (int i = 0; i < PLAYER_COUNT_MAX; ++i)
	{
		std::string player_num = PLAYER_TAG + std::to_string(i + 1);
#pragma omp sections
		{
#pragma omp section
			for (int j = 0; j < PLAYER_COUNT_MAX; ++j)
			{
				if (i == j)
					continue;

				std::string arm_num = ARM_TAG + std::to_string(j + 1);

				bool hit = collisions[arm_num]->GetBoxCollision().Intersects(collisions[player_num]->GetBoxCollision());

				if (!collisions[player_num]->GetAttackHit())
					collisions[player_num]->SetAttackHit(hit);
			}
#pragma omp section

		}
		
	}
}

void CollisionManager::CreateHitBox(std::string& collision_name)
{
	collisions.emplace(collision_name, new Collision);
}
