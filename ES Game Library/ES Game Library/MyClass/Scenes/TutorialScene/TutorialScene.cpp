#include "TutorialScene.h"
#include "../../Managers/SceneManager/SceneManager.h"
#include "../../Managers/ResouceManager/ResouceManager.h"

TutorialScene::TutorialScene()
{
}

TutorialScene::~TutorialScene()
{
}

bool TutorialScene::Initialize()
{

	_tutorial = ResouceManager::Instance().LordSpriteFile(_T("TitleSprite/tutorial.png"));

	Viewport view = GraphicsDevice.GetViewport();
	Vector3 _camera_pos = Vector3(0, 0, -10);
	Vector3 _look_pos = Vector3(0, 0, 0);

	SceneCamera::Instance().SetLookAt(_camera_pos, _look_pos, 0);
	SceneCamera::Instance().SetPerspectiveFieldOfView(60.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);

	return true;
}

int TutorialScene::Update()
{
	auto pad = ControllerManager::Instance().GetController(PLAYER_TAG + std::to_string(1));
	pad->GamePadRefresh();

	if (pad->GetButtonBuffer(GamePad_Button2))
	{
		// キャラ選択のシーンに遷移
		SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::SELECT);
	}

	return 0;
}

void TutorialScene::Draw2D()
{
	SpriteBatch.Draw(*_tutorial, Vector3(0.0f, 0.0f, 10000.0f));
}

