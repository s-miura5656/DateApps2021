#pragma once
#include "../../../ESGLib.h"
#include "../../Data/IData.h"

class PlayerUi
{
private:
	int player_index;//�v���C���[�i���o�[
	std::string tag;
	std::string _arm_tag;

	Vector3 banner_position;//�e�v���C���[�̃o�i�[
	SPRITE  banner_sprite;//�e�v���C���[�̃o�i�[

	static SPRITE  score_font;//�e�v���C���[�̃X�R�A
	int score;

	Vector2 player_position;//�e�v���C���[�̈ʒu
	static FONT player_font;

	static SPRITE test;

	std::vector<Vector3> move_pos;

	std::unique_ptr<IPrayerData> _i_player_data;
	std::unique_ptr<IArmData>    _i_arm_data;
public:
	PlayerUi(const int player_no);
	~PlayerUi();

	bool Initialize(LPCTSTR banner_name, const Vector3& banner_pos);
	int  Update();
	void Draw2D();
};