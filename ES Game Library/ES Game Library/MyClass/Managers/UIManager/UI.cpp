#include "UI.h"
#include"../../Ui/MainUi.h"
#include"../../Ui/ResultUi.h"
#include"../../Ui/TitleUi.h"

MainUiManager::MainUiManager()
{
	_ui = new MainUi;
}

MainUiManager::~MainUiManager()
{
	delete _ui;
}

bool MainUiManager::Initialize()
{
	_ui->Initialize();
	return true;
}

int MainUiManager::Update()
{
	_ui->Update();
	return 0;
}

void MainUiManager::Draw2D()
{
	_ui->Draw2D();
}
