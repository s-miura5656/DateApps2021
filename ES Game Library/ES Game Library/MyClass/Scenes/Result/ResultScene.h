#pragma once

#include "../BaseScene.h"
#include"../../Managers/ControllerManager/ContorollerManager.h"
#include"../../Data/IData.h"
<<<<<<< HEAD

=======
#include"../../Managers/SceneManager/SceneManager.h"
>>>>>>> cf893e710f413e5dde5084f45cb4a2ee7ff9259e
class ResultScene : public BaseScene
{
public:
	ResultScene();
	~ResultScene();
	bool Initialize() override;
	int Update() override;
	void Draw2D() override;
	void Draw3D() override;
	void DrawAlpha3D() override {}

private:
	void AllPosCalculation();
	float PlayerScaleCalculation(int num);
	Vector3 PlayerPositionCalculation(int num);
	Vector2 TextSizeCalculation(int num);
	SPRITE player_rank_num;
	SPRITE background;
	SPRITE totitle;
<<<<<<< HEAD
	FONT font;
	int arrival_count;
	std::vector<Vector3> player_position;
	std::vector<Vector3> player_rank_num_position;
	std::vector<Vector2> point_text_position;
	ANIMATIONMODEL player_model;
	IPrayerData* i_player_data;
	EFFECT shader;
	std::vector<SPRITE>texture;
=======
	FONT txt;
	int num;
	int arrival;
	int fix;
	std::vector<Vector3> pos;
	ANIMATIONMODEL model;
	IPrayerData* _i_player_data;
	EFFECT _shader;
	std::vector<SPRITE>_texture;
>>>>>>> fd01da56e21be856ceeb0274213800e37c991da6
};