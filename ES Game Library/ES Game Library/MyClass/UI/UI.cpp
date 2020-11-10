#include "UI.h"
#include"../../MyClass/Time/Time.h"

UiManager::UiManager()
{

}

UiManager::~UiManager()
{

}

void UiManager::Initialize()
{
	time_limit_font = GraphicsDevice.CreateSpriteFont(_T("SketchFlow Print"), 50);
}
void UiManager::Update()
{


}
void UiManager::Draw()
{
	SpriteBatch.DrawString(time_limit_font, Vector2(0, 100), Color(0, 0, 255), _T("ƒŠƒAƒ‹ƒ^ƒCƒ€:%d"), (TimeManager::Instance().time));
}