#pragma once
#include"../../ESGLib.h"
#include"../Data/StructList.h"
#include"../Managers/ResouceManager/ResouceManager.h"

class UiObject
{
public:
	UiObject() {};
	~UiObject() {};
	
	void Draw2D() { SpriteBatch.Draw(*_sprite, _transform.position, _rect_wh); }
	void SetSprite(tstring texture_path) { _sprite = ResouceManager::Instance().LordSpriteFile(texture_path.c_str()); }
	void SetPosition(Vector3 position) { _transform.position = position; }
	void SetRectWH(RectWH rect_wh) { _rect_wh = rect_wh; }

protected:
	Transform _transform;
	SPRITE _sprite;
	RectWH _rect_wh;
};

