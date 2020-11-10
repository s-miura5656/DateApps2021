// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ES Game Library"));
	_scene_manager = new SceneManager;
	_ui_manager = new UiManager;

	TimeManager::Instance().Initialize();
	_scene_manager->Initialize();
	_ui_manager->Initialize();
	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void GameMain::Finalize()
{
	// TODO: Add your finalization logic here
	delete _ui_manager;
	delete _scene_manager;
}

/// <summary>
/// Allows the game to run logic such as updating the world,
/// checking for collisions, gathering input, and playing audio.
/// </summary>
/// <returns>
/// Scene continued value.
/// </returns>
int GameMain::Update()
{
	// TODO: Add your update logic here
	//_time_manager->Update();
	TimeManager::Instance().Update();
	_scene_manager->Update();

	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_CornflowerBlue);

	GraphicsDevice.BeginScene();

	_scene_manager->Draw3D();

	SpriteBatch.Begin();

	_scene_manager->Draw2D();
	_ui_manager->Draw();

	SpriteBatch.End();

	GraphicsDevice.EndScene();
}
