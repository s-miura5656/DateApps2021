//! @file   SceneManager.h
//! @brief  Sceneを管理するマネージャークラス
//! @author Souta_Miura
//! @date   2020/10/30
#pragma once

#include "../../../ESGLib.h"
#include "../../Data/WordsTable.h"
#include "../ManagerBase.h"

//! 型宣言の時だけ使いたいのでここでBaseSceneの名前だけ使うよって宣言
class BaseScene;

struct ResultData
{
	int ranknum[PLAYER_COUNT_MAX];
	int points[PLAYER_COUNT_MAX];
};

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

	ResultData* GetResultData() { return _result_data; };
	void SetResultData(int[PLAYER_COUNT_MAX], int[PLAYER_COUNT_MAX]);

private:

	//! シングルトンオブジェクトを他で作らせないための記述
	SceneManager(const SceneManager&) = delete;
	void operator=(const SceneManager&) = delete;

	BaseScene* _scene;
	float _viewing_angle;
	Vector3 _camera_pos;
	Vector3 _look_pos;
	Viewport view;
	ResultData* _result_data;
};


class SceneLight
{
public:
	SceneLight() {};
	~SceneLight() {};

	static SceneLight& Instance() {
		static SceneLight instance;
		return instance;
	};

	void SetLightParametor(Light& light) { _light = light; }
	void SetSceneLight() { GraphicsDevice.SetLight(_light); }
	Light GetLight() const { return _light; }

private:
	SceneLight(const SceneLight&)     = delete;
	void operator=(const SceneLight&) = delete;

	Light _light;
};


class SceneCamera
{
public:
	SceneCamera() {};
	~SceneCamera() {};

	static SceneCamera& Instance() {
		static SceneCamera instance;
		return instance;
	};

	void SetSceneCamera() { GraphicsDevice.SetCamera(_camera); }
	void SetLookAt(Vector3 camera_pos, Vector3 look_pos, float angle) { _camera->SetLookAt(camera_pos, look_pos, angle); }
	void SetPerspectiveFieldOfView(const float inFovY, const float inWidth, const float inHeight, const float inZn, const float inZf) {
		_camera->SetPerspectiveFieldOfView(inFovY, inWidth, inHeight, inZn, inZf); }
	void SetView(Vector3 camera_pos, Vector3 camera_angle) { _camera->SetView(camera_pos, camera_angle);} 
	Camera GetCamera() const { return _camera; }
private:
	SceneCamera(const SceneCamera&)    = delete;
	void operator=(const SceneCamera&) = delete;

	Camera _camera;
};

