//! @file   SceneManager.h
//! @brief  Sceneを管理するマネージャークラス
//! @author Souta_Miura
//! @date   2020/10/30
#pragma once

#include "../../../ESGLib.h"
#include "../ManagerBase.h"

//! 型宣言の時だけ使いたいのでここでBaseSceneの名前だけ使うよって宣言
class BaseScene;

class SceneManager : public ManagerBase
{
public:

	//! @enum シーン名
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

	//! シングルトンオブジェクトを他で呼び出す時の記述
	static SceneManager& Instance() {
		static SceneManager instance;
		return instance;
	};

private:

	//! シングルトンオブジェクトを他で作らせないための記述
	SceneManager(const SceneManager&) = delete;
	void operator=(const SceneManager&) = delete;

	CAMERA _camera;
	BaseScene* _scene;
};