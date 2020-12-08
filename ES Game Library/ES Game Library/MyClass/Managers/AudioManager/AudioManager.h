#pragma once
#include"../../../ESGLib.h"
class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	bool Initialize();
	enum{ MAX_PLAY = 4};
	//!�p���`�����˂����Ƃ�
	void PunchShotPlay();
	//!�j��s�̃u���b�N�ɐG�ꂽ��
	void IndestructiblePlay();
	//!�j��\�u���b�N���j�󂳂ꂽ�Ƃ�
	void DestructionPlay();
	//!�M�~�b�N�̂��鏰�ɐG�ꂽ��
	void MapGimmickPlay();
	//!�|�C���g�擾��
	void PointAddition();
	//!�v���C���[�����ʂƂ�
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