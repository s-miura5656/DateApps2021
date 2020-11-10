//! @file   SceneManager.h
//! @brief  Scene���Ǘ�����}�l�[�W���[�N���X
//! @author Souta_Miura
//! @date   2020/10/30
#pragma once

#include "../../../ESGLib.h"
#include "../ManagerBase.h"

//! �^�錾�̎������g�������̂ł�����BaseScene�̖��O�����g������Đ錾
class BaseScene;

class SceneManager : public ManagerBase
{
public:

	//! @enum �V�[����
	enum SceneState
	{
		TITLE,
		MAIN,
		RESULT
	};


	SceneManager();
	~SceneManager();

	void ChangeScene(SceneState scene);

	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;

	//! �V���O���g���I�u�W�F�N�g�𑼂ŌĂяo�����̋L�q
	static SceneManager& Instance() {
		static SceneManager instance;
		return instance;
	};

private:

	//! �V���O���g���I�u�W�F�N�g�𑼂ō�点�Ȃ����߂̋L�q
	SceneManager(const SceneManager&) = delete;
	void operator=(const SceneManager&) = delete;

	CAMERA _camera;
	BaseScene* _scene;
};