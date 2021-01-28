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

	_banner_sprite = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/banner_0127.png"));
	_banner_pos = UiParametor::Instance().GetBannerPosition(player);
	_banner_rw  = UiParametor::Instance().GetBannerRectWH(player);

	//_banner_status = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/status.png"));
	//_banner_status_pos = UiParametor::Instance().GetStatusBannerPsition(player);
	//_status_rw = UiParametor::Instance().GetStatusBannerRectWH(player);

	_player_icon = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/player_icon.png"));
	_player_icon_pos = UiParametor::Instance().GetPlayerIconPosition(player);
	_player_joy_icon_rw = UiParametor::Instance().GetPlayerJoyIconRectwh(player);
	_player_normal_icon_rw = UiParametor::Instance().GetPlayerNormalIconRectwh(player);

	ranking = ResouceManager::Instance().LordSpriteFile(_T("BannerFrameSprite/runking.png"));
	score_font = ResouceManager::Instance().LordSpriteFile(_T("NumberSprite/namber.png"));

	_font_size = 0.5;
	score = 0;

	return true;
}

int PlayerUi::Update()
{
	auto rank_point = _i_player_data->GetRankingPoint(tag);
	auto player_num = GraphicsDevice.WorldToScreen(_i_player_data->GetPosition(tag));

	player_pos.x = player_num.x;
	player_pos.y = player_num.y;
	player_pos.z = 0;

	if (rank_point > score) {
		score += 10;
		if (rank_point < score) {
			score = rank_point;
		}
	}
	
	return 0;
}

void PlayerUi::Draw2D()
{
	//IPrayerData* i_player_data = new IPrayerData;

	//! �o�i�[
	SpriteBatch.Draw(*_banner_sprite, _banner_pos, _banner_rw);

	//! �X�e�[�^�X
	//SpriteBatch.Draw(*_banner_status, _banner_status_pos, _status_rw);

	//! ���ʂɉ����ăv���C���[�A�C�R��
	if (_i_player_data->GetRankNum(tag) == FIRST)
	{
		SpriteBatch.Draw(*_player_icon, _player_icon_pos, _player_joy_icon_rw);
	}
	else
	{
		SpriteBatch.Draw(*_player_icon, _player_icon_pos, _player_normal_icon_rw);
	}

	//! �v���C���[����ɏ��ʕ\��
	SpriteBatch.Draw(*ranking, player_pos,RectWH(_i_player_data->GetRankNum(tag) * 128,0,128,128),
		(DWORD)Color_White, Vector3(0, 0, 0), Vector3(0, 0, 0), 0.7f);
	
	//�o�i�[�X�R�A�A�j���[�V����
	SpriteElement se;
	se = score_font;

	se.position = _banner_pos + Vector3((10 * _font_size) + 90, 55, -1);
	se.srcRect = RectWH((int)(score / 1000) * 64, 0, 64, 64);
	se.anchorPoint = Vector3(32 * _font_size, 32 * _font_size, 0);
	se.SetScale(_font_size);
	SpriteBatch.Draw(se);

	se.position = _banner_pos + Vector3((74 * _font_size) + 90, 55, -1);
	se.srcRect = RectWH((int)((score % 1000) / 100) * 64, 0, 64, 64);
	SpriteBatch.Draw(se);

	se.position = _banner_pos + Vector3((138 * _font_size) + 90, 55, -1);
	se.srcRect = RectWH((int)((score % 1000) % 100 / 10) * 64, 0, 64, 64);
	SpriteBatch.Draw(se);

	se.position = _banner_pos + Vector3((204 * _font_size) + 90, 55, -1);
	se.srcRect = RectWH((int)((score % 1000) % 100 % 10) * 64, 0, 64, 64);
	SpriteBatch.Draw(se);

	//delete i_player_data;
}
