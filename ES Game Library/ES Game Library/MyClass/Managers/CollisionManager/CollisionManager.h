//! @file   CollisionManager.h
//! @brief  当たり判定用用の管理クラス
//! @author Souta_Miura
//! @date   2020/11/05
#pragma once

#include "../ManagerBase.h"
#include "../../Collision/Collision.h"
#include "../../Data/IPlayerData.h"

class CollisionManager : public ManagerBase
{
public:
	CollisionManager();
	~CollisionManager();

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;

	void UpdateHitBoxs(std::string tag, int max_loop_count);
	void DrawHitBoxs(std::string tag, int max_loop_count);
	
	
	void InitializePlayerHitBoxs();
	void InitializeArmHitBoxs();
	
	void UpdateArmHitBoxs();
	void CreateHitBox(std::string& collision_name);

	static CollisionManager& Instance() {
		static CollisionManager instance;
		return instance;
	};

private:
	CollisionManager(const CollisionManager&) = delete;
	void operator=(const CollisionManager&) = delete;

	IPrayerData* i_player_data;
	std::map<std::string, Collision*> collisions;
};
