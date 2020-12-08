#pragma once
#include"../../../ESGLib.h"
class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	bool Initialize();
	enum{ MAX_PLAY = 4};
	//!パンチが発射されるとき
	void PunchShotPlay();
	//!破壊不可のブロックに触れた時
	void IndestructiblePlay();
	//!破壊可能ブロックが破壊されたとき
	void DestructionPlay();
	//!ギミックのある床に触れた時
	void MapGimmickPlay();
	//!ポイント取得時
	void PointAddition();
	//!プレイヤーが死ぬとき
	void Explosion();
	void MainBgmPlay();
private:
	SOUND _punchshot[MAX_PLAY];
	SOUND _indestructible[MAX_PLAY];
	SOUND _destruction[MAX_PLAY];
	SOUND _mapgimmick[MAX_PLAY];
	SOUND _pointaddition[MAX_PLAY];
	SOUND _explosion[MAX_PLAY];
	MUSIC _mainbgm;
};