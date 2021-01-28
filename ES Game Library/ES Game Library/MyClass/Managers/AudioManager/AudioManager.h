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
	//! スカアイテム音
	void PowerDownPlay();
	//! サンダー取得音
	void ThunderPlay();
	//!メイン終了ホイッスル
	void GameEndWhistlePlay();
	//!タイトルBGMの開始
	void TitleBgmPlay();
	//!タイトルBGMの終了
	void TitleBgmStop();
	//!メインBGMの開始
	void MainBgmPlay();
	//!メインBGMの終了
	void MainBgmStop();
	//!メインBGMの開始
	void SpeedUpMainBgmPlay();
	//!メインBGMの終了
	void SpeedUpMainBgmStop();
	//!リザルトBGMの開始
	void ResultBgmPlay();
	//!リザルトBGMの終了
	void ResultBgmStop();
	//!
	void SelectPlay();
	//!
	void CancelPlay();
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
	SOUND _select[MAX_PLAY];
	SOUND _cancel[MAX_PLAY];
	SOUND _whistle;
	SOUND _signal;
	MUSIC _titlebgm;
	MUSIC _mainbgm;
	MUSIC _speedupmainbgm;
	MUSIC _resultbgm;
	bool  _whistle_flag = false;
};