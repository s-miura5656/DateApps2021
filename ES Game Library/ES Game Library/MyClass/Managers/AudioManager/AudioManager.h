#pragma once
#include"../../../ESGLib.h"
class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	bool Initialize();
	enum{ MAX_PLAY = 4};
	//!�Q�[�����n�܂�z�C�b�X��
	void GameStartWhistlePlay();
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
	void ExplosionPlay();
	//!�p���[�A�b�v�A�C�e���擾��
	void PowerUpPlay();
	//! �p���[�_�E���擾��
	void PowerDownPlay();
	//! �T���_�[�擾��
	void ThunderPlay();
	//!���C���I���z�C�b�X��
	void GameEndWhistlePlay();
	//!���C��BGM
	void MainBgmPlay();
	//!���C��BGM�̏I��
	void MainBgmStop();
	//! �V���O���g���I�u�W�F�N�g�𑼂ŌĂяo�����̋L�q
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