#pragma once

#include "../../../ESGLib.h"
#include <XInput.h>
#include <Windows.h>

Vector2 const STICK_CENTER = Vector2_Zero;
int const PAD_COUNT_MAX = 4;

enum BUTTON_INFO
{
    BUTTON_A,
    BUTTON_B,
    BUTTON_Y,
    BUTTON_X,
    BUTTON_START,
    BUTTON_BACK,
    BUTTON_LEFT_SHOULDER,
    BUTTON_RIGHT_SHOULDER,
    BUTTON_LEFT_THUMB,
    BUTTON_RIGHT_THUMB,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_RIGHT,
    MAX_BUTTON_INFO,
};

enum TRIGGER_INFO
{
    LEFT_TRIGGER,
    RIGHT_TRIGGER,
    MAX_TRIGGER_INFO,
    TRIGGER_TRESHOLD = XINPUT_GAMEPAD_TRIGGER_THRESHOLD,
};

enum STICK_INFO
{
    LEFT_STICK,
    RIGHT_STICK,
    MAX_STICK_INFO,
};

enum INPUT_STATE
{
    NOT_PUSH,
    PUSH,
};

class BaseInput;

class InputManager
{
public:
	InputManager();
	~InputManager();

	void CreateXInputGamePad(std::string tag);
    void CreateDInputGamePad(std::string tag, int pad_count);
    BaseInput* GetGamePad(std::string tag);
    
    static InputManager& Instance() {
        static InputManager instance;
        return instance;
    };

private:
    InputManager(const InputManager&) = delete;
    void operator=(const InputManager&) = delete;

	bool XInputActive(int pad_num);

	std::map<std::string, std::unique_ptr<BaseInput>> _game_pads;

    int _pad_num;
    int _xpad_count;
    int _dpad_count;
};

class BaseInput
{
public:
	BaseInput() {};
    virtual ~BaseInput() {};

    virtual void Refresh()                = 0;
	virtual bool Button(int key_info)     = 0;
	virtual bool ButtonDown(int key_info) = 0;
	virtual bool ButtonUp(int key_info)   = 0;
    virtual float Trigger(int key_info)   = 0;
    virtual Vector2 Stick(int key_info)   = 0;

protected:
	int _pad_number = 0;
};

class XInput : public BaseInput
{
public:
	XInput(int pad_number);
	~XInput();

    void Refresh()                override;
	bool Button(int key_info)     override;
	bool ButtonDown(int key_info) override;
	bool ButtonUp(int key_info)   override;
    float Trigger(int key_info)   override;
    Vector2 Stick(int key_info)   override;

private:
    //! button
    int _button_info[BUTTON_INFO::MAX_BUTTON_INFO];
    INPUT_STATE _button_state[BUTTON_INFO::MAX_BUTTON_INFO];
    bool _button_enter_flag[BUTTON_INFO::MAX_BUTTON_INFO];
    bool _button_exit_flag;
    INPUT_STATE InputButtonState(int key_info);
    
    XINPUT_STATE GetXState();

    XINPUT_STATE _x_state;
};

class DirectInput : public BaseInput
{
public:
    DirectInput(int pad_number);
    ~DirectInput();

    void Refresh()                override;
    bool Button(int key_info)     override;
    bool ButtonDown(int key_info) override;
    bool ButtonUp(int key_info)   override;
    float Trigger(int key_info)   override;
    Vector2 Stick(int key_info)   override;
private:
    //! button
    int _button_info[BUTTON_INFO::MAX_BUTTON_INFO];
    int _trigger_info[TRIGGER_INFO::MAX_TRIGGER_INFO];

    int const move_value_constant = 1000;

    GamePadBuffer _pad_buffer;
    GamePadState  _pad_state;
};
