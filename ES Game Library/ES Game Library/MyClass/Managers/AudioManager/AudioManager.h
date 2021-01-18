#pragma once
#include"../../../ESGLib.h"
class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	bool Initialize();
	enum{ MAX_PLAY = 4};
	//!ゲームが始まるホイッスル
	void GameStartWhistlePlay();
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
	void ExplosionPlay();
	//!パワーアップアイテム取得音
	void PowerUpPlay();
	//! パワーダウン取得音
	void PowerDownPlay();
	//! サンダー取得音
	void ThunderPlay();
	//!メイン終了ホイッスル
	void GameEndWhistlePlay();
	//!メインBGM
	void MainBgmPlay();
	//!メインBGMの終了
	void MainBgmStop();
	//! シングルトンオブジェクトを他で呼び出す時の記述
	static AudioManager& Instance() {
		static AudioManager instance;
		return instance;
	};
private:
	SOUND _punchshot[MAX_PLAY];
	SOUND _indestructible[MAX_PLAY];
	SOUND _destruction[MAX_PLAY];
	SOUND _mapgimmick[MAX_PLAY];
	SOUND _pointaddition[MAX_PLAY];
	SOUND _explosion[MAX_PLAY];
	SOUND _powerup[MAX_PLAY];
	SOUND _powerdown[MAX_PLAY];
	SOUND _thunder[MAX_PLAY];
	SOUND _whistle;
	SOUND _signal;
	MUSIC _mainbgm;
	bool  _whistle_flag = false;
};