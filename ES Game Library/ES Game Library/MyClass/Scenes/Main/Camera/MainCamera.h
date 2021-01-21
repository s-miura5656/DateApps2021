#include "../../../../ESGLib.h"
class MainCamera
{
public:
	MainCamera();
	~MainCamera();

	static MainCamera& Instance() {
		static MainCamera instance;
		return instance;
	};

	bool Initialize();
	int Update();
	void TimeReset() { _time = 1; }
private:
	void Shake();
	Vector3 camera_pos = Vector3(7, 16, -12.0f);
	Vector3 camera_angle = Vector3(60, 0, 0);
	float _time = 9999;
	float _num = 1;
	bool  _shake_flag = false;
};
