#include"MainCamera.h"
#include "../../../Managers/SceneManager/SceneManager.h"
MainCamera::MainCamera()
{
}

MainCamera::~MainCamera()
{
}

bool MainCamera::Initialize()
{
	auto view = GraphicsDevice.GetViewport();
	camera_pos = Vector3(7, 26.7f, -20.6f);
	camera_angle = Vector3(60.7, 0, 0);
	SceneCamera::Instance().SetView(camera_pos, camera_angle);
	SceneCamera::Instance().SetPerspectiveFieldOfView(25.3, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);
	return false;
}

int MainCamera::Update()
{
	Shake();
	return 0;
}

void MainCamera::Shake()
{
	if (_time >= 60)
	{
		SceneCamera::Instance().SetView(Vector3(7, 26.7f, -20.6f), Vector3(60.7, 0, 0));
		return;
	}

	float x = 7 + ((60 / _time) * _num) * 0.015;

	_time++;
	_num *= -1;
	SceneCamera::Instance().SetView(Vector3(x, 26.7f, -20.6f), Vector3(60.7, 0, 0));
}

