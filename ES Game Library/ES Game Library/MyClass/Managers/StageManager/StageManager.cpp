#include "StageManager.h"
#include "../../Stage/Stage_1/Stage.h"

StageManager::StageManager()
{
	_stage = new Stage;
}

StageManager::~StageManager()
{
	delete _stage;
}

bool StageManager::Initialize()
{
	_stage->Initialize();

	return true;
}

int StageManager::Update()
{
	_stage->Update();

	return 0;
}

void StageManager::Draw2D()
{
	_stage->Draw2D();
}

void StageManager::Draw3D()
{
	_stage->Draw3D();
}
