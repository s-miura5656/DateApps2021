#include "UiParametor.h"

UiParametor::UiParametor()
{

	_bunner_position[PLAYER1] = Vector3(10, 200, 1);
	_bunner_position[PLAYER2] = Vector3(1280 - 250, 200, 1);
	_bunner_position[PLAYER3] = Vector3(10, 500, 1);
	_bunner_position[PLAYER4] = Vector3(1280 - 250, 500, 1);

	_bunner_rectwh[PLAYER1] = RectWH(  0, 0, 256, 64);
	_bunner_rectwh[PLAYER2] = RectWH(256, 0, 256, 64);
	_bunner_rectwh[PLAYER3] = RectWH(512, 0, 256, 64);
	_bunner_rectwh[PLAYER4] = RectWH(768, 0, 256, 64);

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		_status_bunner_position[i] = _bunner_position[i] + Vector3(0, 74, 0);
	}
	
	_status_rectwh[PLAYER1] = RectWH(  0, 0, 256, 128);
	_status_rectwh[PLAYER2] = RectWH(256, 0, 256, 128);
	_status_rectwh[PLAYER3] = RectWH(512, 0, 256, 128);
	_status_rectwh[PLAYER4] = RectWH(768, 0, 256, 128);

	for (int i = 0; i < PLAYER_COUNT_MAX; i++)
	{
		_player_icon_position[i] = _bunner_position[i] + Vector3(100, -128, -10);
	}
	
	_player_normal_icon_rectwh[PLAYER1] = RectWH(  0, 128, 128, 128);
	_player_normal_icon_rectwh[PLAYER2] = RectWH(128, 128, 128, 128);
	_player_normal_icon_rectwh[PLAYER3] = RectWH(256, 128, 128, 128);
	_player_normal_icon_rectwh[PLAYER4] = RectWH(384, 128, 128, 128);

	_player_joy_icon_rectwh[PLAYER1] = RectWH(  0, 0, 128, 128);
	_player_joy_icon_rectwh[PLAYER2] = RectWH(128, 0, 128, 128);
	_player_joy_icon_rectwh[PLAYER3] = RectWH(256, 0, 128, 128);
	_player_joy_icon_rectwh[PLAYER4] = RectWH(384, 0, 128, 128);


}