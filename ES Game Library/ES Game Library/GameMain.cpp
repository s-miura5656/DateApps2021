// #include "Extension\DirectX11\DXGraphics11.hpp"
#include "StdAfx.h"
#include "GameMain.h"
#include "MyClass/Managers/SceneManager/SceneManager.h"

/// <summary>
/// Allows the game to perform any initialization it needs to before starting to run.
/// This is where it can query for any required services and load all of your content.
/// Initialize will enumerate through any components and initialize them as well.
/// </summary>
bool GameMain::Initialize()
{
	// TODO: Add your initialization logic here
	WindowTitle(_T("ロケパンファイターズ"));

	Effekseer.Attach(GraphicsDevice);
	SceneManager::Instance().Initialize();
	SceneManager::Instance().SetSceneNumber(SceneManager::SceneState::TITLE);
	SceneManager::Instance().ChangeScene();

	//hdr = GraphicsDevice.CreateHDRRenderTarget(1280, 720, DepthFormat_Unknown);
	//_shader = GraphicsDevice.CreateEffectFromFile(_T("HLSL/Hdr.hlsl"));
	//_shader->SetParameter("exposure", 0.5f);
	return true;
}

/// <summary>
/// Finalize will be called once per game and is the place to release
/// all resource.
/// </summary>
void GameMain::Finalize()
{
	// TODO: Add your finalization logic here
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
	SceneManager::Instance().ChangeScene();
	SceneManager::Instance().Update();
	Effekseer.Update();
	return 0;
}

/// <summary>
/// This is called when the game should draw itself.
/// </summary>
void GameMain::Draw()
{
	// TODO: Add your drawing code here
	GraphicsDevice.Clear(Color_Black);

	GraphicsDevice.BeginScene();

	//GraphicsDevice.SetRenderTarget(hdr);
	//GraphicsDevice.Clear(Color_Black);

	SpriteBatch.Begin();

	SceneManager::Instance().Draw2D();

	SpriteBatch.End();

	SceneManager::Instance().Draw3D();

	GraphicsDevice.BeginAlphaBlend();
	GraphicsDevice.SetRenderState(CullMode_None);
	SceneManager::Instance().DrawAlpha3D();
	GraphicsDevice.SetRenderState(CullMode_CullCounterClockwiseFace);
	GraphicsDevice.EndAlphaBlend();

	Effekseer.SetCamera(SceneCamera::Instance().GetCamera());
	Effekseer.Draw();

	//GraphicsDevice.RenderTargetToBackBuffer(hdr, _shader);
	GraphicsDevice.EndScene();
}
