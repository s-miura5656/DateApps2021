#include "../../ESGLib.h"
#include "Arm/Arm.h"
#include "../Collision/HitBox.h"
#include "../Data/IData.h"
#include "../Managers/ControllerManager/ContorollerManager.h"

class PlayerBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

	virtual bool Initialize() { return true; }
	virtual int Update() { return 0; }
	virtual void Draw2D();
	virtual void Draw3D();

	Vector3 GetPos()  { return _model->GetPosition(); }
	float GetAngle()  { return _angle; }
	MODEL GetPlayer() { return _model; }
	
	float PlayerSpeed();

	void CreateArm();
	void DestroyArm();
	std::string GetTag() const { return _tag; }
	int GetPlayerNumber() const { return (*_tag.rbegin()) - '0'; }

protected:
	MODEL _model;
	FONT _font;

	const float scale		 = 0.004f;
	const float player_scale = 1.f;
	float _angle			 = 0.f;
	float _speed			 = 0.f;
	float _weight			 = 0.f;
	float _move_speed		 = 0.f;
	float _distance			 = FLT_MAX;
	Vector3 _position		 = Vector3_Zero;
	Vector3 _old_pos		 = Vector3_Zero;
	ArmBase* _arm = nullptr;
	IPrayerData* _iplayer_data;
	IArmData* _iarm_data;
	IMapData* _imap_data;
	std::unique_ptr<HitBox> _hit_box;
	std::string _tag;
	std::string _arm_tag;

	int a = 0;
};
