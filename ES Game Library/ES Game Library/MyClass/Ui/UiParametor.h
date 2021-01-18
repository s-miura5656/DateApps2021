#pragma once

#include "../../ESGLib.h"
#include "../Data/StructList.h"

class UiParametor
{
public:

	//! friend 一方的にprivateを取得できる
	friend class IPlayersFrameUI;
	friend class IPlayersPoseUI;
	~UiParametor() {};
	
	static UiParametor& Instance() {
		static UiParametor instance;
		return instance;
	};

	void CreateUiTransform(std::string tag) 
	{ 
		//! プッシュバックに似たもの 
		_frame_transforms.emplace_hint(_frame_transforms.end(), tag, _base_transform);
		_pose_transforms.emplace_hint(_pose_transforms.end(), tag, _base_transform);
		_frame_rect.emplace_hint(_frame_rect.end(), tag, _base_rect);
		_joy_rect.emplace_hint(_joy_rect.end(), tag, _base_rect);
		

	}

	Vector3 GetBannerPosition(int player) const { return _bunner_position[player]; }
	RectWH GetBannerRectWH(int player)const { return _bunner_rectwh[player]; }

	Vector3 GetStatusBannerPsition(int player) const { return _status_bunner_position[player]; }
	RectWH GetStatusBannerRectWH(int player)const { return _status_rectwh[player]; }

	Vector3 GetPlayerIconPosition(int player) const { return _player_icon_position[player]; }
	RectWH GetPlayerJoyIconRectwh(int player)const { return _player_joy_icon_rectwh[player]; }
	RectWH GetPlayerNormalIconRectwh(int player)const { return _player_normal_icon_rectwh[player]; }

	
private:
	UiParametor();
	UiParametor(const UiParametor&)	   = delete;
	void operator=(const UiParametor&) = delete;



	//! map 連想配列　配列に名前を指定できる  
	std::map<std::string, Transform> _frame_transforms;
	Transform _base_transform;

	std::map<std::string, Transform> _pose_transforms;

	std::map<std::string, RectWH> _frame_rect;
	RectWH _base_rect = RectWH(0, 0, 0, 0);

	std::map<std::string, RectWH> _joy_rect;

	Vector3 _bunner_position[PLAYER_COUNT_MAX];
	RectWH _bunner_rectwh[PLAYER_COUNT_MAX];

	Vector3 _status_bunner_position[PLAYER_COUNT_MAX];
	RectWH _status_rectwh[PLAYER_COUNT_MAX];
	
	Vector3 _player_icon_position[PLAYER_COUNT_MAX];
	RectWH _player_normal_icon_rectwh[PLAYER_COUNT_MAX];
	RectWH _player_joy_icon_rectwh[PLAYER_COUNT_MAX];

};


class IPlayersFrameUI
{
public:
	IPlayersFrameUI() {};
	~IPlayersFrameUI() {};
	
	void SetTransform(std::string tag, Transform transform)  { UiParametor::Instance()._frame_transforms[tag] = transform; }
	Transform GetTransform(std::string tag)            const { return UiParametor::Instance()._frame_transforms[tag]; }

	void SetPosition(std::string tag, Vector3 position)      { UiParametor::Instance()._frame_transforms[tag].position = position; }
	Vector3 GetPosition(std::string tag)		       const { return UiParametor::Instance()._frame_transforms[tag].position; }

	void SetRotation(std::string tag, Vector3 rotation)      { UiParametor::Instance()._frame_transforms[tag].rotation = rotation; }
	Vector3 GetRotation(std::string tag)               const { return UiParametor::Instance()._frame_transforms[tag].rotation; }

	void SetScale(std::string tag, Vector3 scale)            { UiParametor::Instance()._frame_transforms[tag].scale = scale; }
	Vector3 GetScale(std::string tag)                  const { return UiParametor::Instance()._frame_transforms[tag].scale; }

	void SetRect(std::string tag, RectWH rect_wh)           { UiParametor::Instance()._frame_rect[tag] = rect_wh; }
	RectWH GetRect(std::string tag)                   const { return UiParametor::Instance()._frame_rect[tag]; }
};

class IPlayersPoseUI
{
public:
	IPlayersPoseUI() {};
	~IPlayersPoseUI() {};

	void SetTransform(std::string tag, Transform transform)  { UiParametor::Instance()._pose_transforms[tag] = transform; }
	Transform GetTransform(std::string tag)            const { return UiParametor::Instance()._pose_transforms[tag]; }

	void SetPosition(std::string tag, Vector3 position)      { UiParametor::Instance()._pose_transforms[tag].position = position; }
	Vector3 GetPosition(std::string tag)		       const { return UiParametor::Instance()._pose_transforms[tag].position; }

	void SetRotation(std::string tag, Vector3 rotation)      { UiParametor::Instance()._pose_transforms[tag].rotation = rotation; }
	Vector3 GetRotation(std::string tag)               const { return UiParametor::Instance()._pose_transforms[tag].rotation; }

	void SetScale(std::string tag, Vector3 scale)            { UiParametor::Instance()._pose_transforms[tag].scale = scale; }
	Vector3 GetScale(std::string tag)                  const { return UiParametor::Instance()._pose_transforms[tag].scale; }

	void SetRect(std::string tag, RectWH rect_wh)         { UiParametor::Instance()._joy_rect[tag] = rect_wh; }
	RectWH GetRect(std::string tag)                 const { return UiParametor::Instance()._joy_rect[tag]; }

	
};

