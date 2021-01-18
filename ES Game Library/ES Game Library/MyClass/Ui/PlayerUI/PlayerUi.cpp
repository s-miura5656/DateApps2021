#include "PlayerUi.h"
#include "../../Managers/ResouceManager/ResouceManager.h"
#include "../UiParametor.h"
#include "../../Data/IData.h"

PlayerUi::PlayerUi(int player_no) /*: player_index(player_no), _banner_pos(0, 0, 0), _banner_rw(0, 0, 0, 0)*/
{
	tag = PLAYER_TAG + std::to_string(player_no);
	
}

PlayerUi::~PlayerUi()
{
	
}

bool PlayerUi::Initialize(int player)
{
	
	auto player_num = GraphicsDevice.WorldToScreen(_i_player_data->GetPosition(tag));

	player_pos.x = player_num.x;
	player_pos.y = player_num.y;

	_banner_sprite = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/score_0110.png"));
	_banner_pos = UiParametor::Instance().GetBannerPosition(player);
	_banner_rw  = UiParametor::Instance().GetBannerRectWH(player);

	_banner_status = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/status.png"));
	_banner_status_pos = UiParametor::Instance().GetStatusBannerPsition(player);
	_status_rw = UiParametor::Instance().GetStatusBannerRectWH(player);

	_player_icon = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/player_icon.png"));
	_player_icon_pos = UiParametor::Instance().GetPlayerIconPosition(player);
	_player_joy_icon_rw = UiParametor::Instance().GetPlayerJoyIconRectwh(player);
	_player_normal_icon_rw = UiParametor::Instance().GetPlayerNormalIconRectwh(player);

	ranking = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/runking.png"));
	ranking_rw = UiParametor::Instance().GetPlayerRankingRectwh(player);

	
	return true;
}

int PlayerUi::Update()
{
	
	
	return 0;
}

void PlayerUi::Draw2D()
{
	IPrayerData* i_player_data = new IPrayerData;
	SpriteBatch.Draw(*_banner_sprite, _banner_pos, _banner_rw);
	SpriteBatch.Draw(*_banner_status, _banner_status_pos, _status_rw);

	if (i_player_data->GetRankNum(tag) == FIRST)
	{
		SpriteBatch.Draw(*_player_icon, _player_icon_pos, _player_joy_icon_rw);

	}
	else
	{
		SpriteBatch.Draw(*_player_icon, _player_icon_pos, _player_normal_icon_rw);
	}

	SpriteBatch.Draw(*ranking, player_pos,RectWH(i_player_data->GetRankNum(tag) * 128,0,128,128),
		(DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.7f);
		
	delete i_player_data;
}
