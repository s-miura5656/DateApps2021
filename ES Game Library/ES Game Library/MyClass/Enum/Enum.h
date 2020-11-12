#include "../../ESGLib.h"

//プレイヤーのアニメーション
enum { WAIT, WALK, DESTRUCTION, ATTACK, ANIMATION_ALL_TYPE };

enum PunchType{UNCLASP_PUNCH, SET_PUNCH, PUNCH_MAX};

//プレイヤーの状態
enum { NO_PUNCH, PUNCH, RETURN_PUNCH};
enum { DEATH, ALIVE};

//gamepad
enum{PLAYER1,PLAYER2,PLAYER3,PLAYER4,PLAYER_MAX};

enum { PAD_BUFFER, PAD_STATE };