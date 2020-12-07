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
	
	/*MainUi* ui = (MainUi*)_ui;
	KeyboardState key = Keyboard->GetState();
	if (key.IsKeyDown(Keys_D1))
		ui->SetDamege(0, 4);
	if (key.IsKeyDown(Keys_D2))
		ui->SetDamege(1, 4);
	if (key.IsKeyDown(Keys_D3))
		ui->SetDamege(2, 4);
	if (key.IsKeyDown(Keys_D4))
		ui->SetDamege(3, 4);*/

	return 0;
}

void MainUiManager::Draw2D()
{
	_ui->Draw2D();
}
