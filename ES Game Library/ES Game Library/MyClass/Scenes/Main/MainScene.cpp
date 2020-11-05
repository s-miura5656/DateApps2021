#include "MainScene.h"
#include "../../Managers/ItemManager/ItemManager.h"


MainScene::MainScene()
{
	item_manager = new ItemManager;

}

MainScene::~MainScene()
{
	delete item_manager;
}

bool MainScene::Initialize()
{	
	/**
	* @brief ライトの初期設定
	*/
	Light light;
	light.Type = Light_Directional;
	light.Direction = Vector3(0, 1, 1);
	light.Diffuse = Color(1.0f, 1.0f, 1.0f);
	light.Ambient = Color(1.0f, 1.0f, 1.0f);
	light.Specular = Color(1.0f, 1.0f, 1.0f);
	GraphicsDevice.SetLight(light);

	/**
	* @brief カメラの初期設定
	*/
	Viewport view = GraphicsDevice.GetViewport();
	camera->SetView(Vector3(10, 20, 2), Vector3(75, 0, 0));
	camera->SetPerspectiveFieldOfView(45.0f, (float)view.Width, (float)view.Height, 1.0f, 10000.0f);


	Material player_mtrl;
	player_mtrl.Diffuse = Color(255.0f, 0.0f, 0.0f, 1.0f);
	player_mtrl.Ambient = Color(255.0f, 0.0f, 0.0f, 1.0f);

	//プレイヤー
	player1.FileInitialize(_T("player/robot_02.X"));
	player1.Initialize(PLAYER1, Vector3(1, 0, 13), player_mtrl);//パッドの番号、プレイヤーの初期座標

	player_mtrl.Diffuse = Color(0.0f, 255.0f, 0.0f, 0.3f);
	player_mtrl.Ambient = Color(0.0f, 255.0f, 0.0f, 0.3f);

	player2.FileInitialize(_T("player/robot_02.X"));
	player2.Initialize(PLAYER2, Vector3(17, 0, 13), player_mtrl);

	player_mtrl.Diffuse = Color(0.0f, 0.0f, 255.0f, 0.3f);
	player_mtrl.Ambient = Color(0.0f, 0.0f, 255.0f, 0.3f);

	player3.FileInitialize(_T("player/robot_02.X"));
	player3.Initialize(PLAYER3, Vector3(1, 0, 1), player_mtrl);

	player_mtrl.Diffuse = Color(255.0f, 255.0f, 0.0f, 0.3f);
	player_mtrl.Ambient = Color(255.0f, 255.0f, 0.0f, 0.3f);

	player4.FileInitialize(_T("player/robot_02.X"));
	player4.Initialize(PLAYER4, Vector3(17, 0, 1), player_mtrl);

	

	//ゲームパッド
	InputDevice.CreateGamePad(PLAYER_MAX);

	item_manager->Initialize();

	return true;
}

int MainScene::Update()
{
	player1.Update();
	player2.Update();
	player3.Update();
	player4.Update();

	item_manager->Update();

	return 0;
}

void MainScene::Draw2D()
{
	item_manager->Draw2D();
}

void MainScene::Draw3D()
{
	GraphicsDevice.SetCamera(camera);

	player1.Draw();
	player2.Draw();
	player3.Draw();
	player4.Draw();

	item_manager->Draw3D();
}
