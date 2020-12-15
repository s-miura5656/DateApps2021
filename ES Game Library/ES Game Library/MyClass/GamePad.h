//--------------------------------------------------------------------------------------
// File: GamePad.h
//--------------------------------------------------------------------------------------
#pragma once

struct Buttons
{
    bool a;
    bool b;
    bool x;
    bool y;
    bool leftStick;
    bool rightStick;
    bool leftShoulder;
    bool rightShoulder;
    union
    {
        bool back;
        bool view;
    };
    union
    {
        bool start;
        bool menu;
    };
};

struct DPad
{
    bool up;
    bool down;
    bool right;
    bool left;
};

struct ThumbSticks
{
    float leftX;
    float leftY;
    float rightX;
    float rightY;
};

struct Triggers
{
    float left;
    float right;
};

class XGamePad
{
public:
    XGamePad();

    XGamePad(XGamePad const&) = delete;
    XGamePad& operator=(XGamePad const&) = delete;

    virtual ~XGamePad();

    struct State
    {
        bool        connected;
        Buttons     buttons;
        DPad        dpad;
        ThumbSticks thumbSticks;
        Triggers    triggers;

        bool __cdecl IsConnected() const { return connected; }

        // Is the button pressed currently?
        bool __cdecl IsAPressed() const { return buttons.a; }
        bool __cdecl IsBPressed() const { return buttons.b; }
        bool __cdecl IsXPressed() const { return buttons.x; }
        bool __cdecl IsYPressed() const { return buttons.y; }

        bool __cdecl IsLeftStickPressed() const { return buttons.leftStick; }
        bool __cdecl IsRightStickPressed() const { return buttons.rightStick; }

        bool __cdecl IsLeftShoulderPressed() const { return buttons.leftShoulder; }
        bool __cdecl IsRightShoulderPressed() const { return buttons.rightShoulder; }

        bool __cdecl IsBackPressed() const { return buttons.back; }
        bool __cdecl IsViewPressed() const { return buttons.view; }
        bool __cdecl IsStartPressed() const { return buttons.start; }
        bool __cdecl IsMenuPressed() const { return buttons.menu; }

        bool __cdecl IsDPadDownPressed() const { return dpad.down; }
        bool __cdecl IsDPadUpPressed() const { return dpad.up; }
        bool __cdecl IsDPadLeftPressed() const { return dpad.left; }
        bool __cdecl IsDPadRightPressed() const { return dpad.right; }

        float __cdecl IsLeftThumbStickY() const { return thumbSticks.leftY; }
        float __cdecl IsLeftThumbStickX() const { return thumbSticks.leftX; }

        float __cdecl IsRightThumbStickY() const { return thumbSticks.rightY; }
        float __cdecl IsRightThumbStickX() const { return thumbSticks.rightX; }

        float __cdecl IsLeftTriggerPressed() const { return triggers.left; }
        float __cdecl IsRightTriggerPressed() const { return triggers.right; }
    };

    class ButtonStateTracker
    {
    public:
        enum ButtonState
        {
            UP = 0,         // Button is up
            HELD = 1,       // Button is held down
            RELEASED = 2,   // Button was just released
            PRESSED = 3,    // Buton was just pressed
        };

        ButtonState a;
        ButtonState b;
        ButtonState x;
        ButtonState y;

        ButtonState leftStick;
        ButtonState rightStick;

        ButtonState leftShoulder;
        ButtonState rightShoulder;

        union
        {
            ButtonState back;
            ButtonState view;
        };

        union
        {
            ButtonState start;
            ButtonState menu;
        };

        ButtonState dpadUp;
        ButtonState dpadDown;
        ButtonState dpadLeft;
        ButtonState dpadRight;

        ButtonState leftStickUp;
        ButtonState leftStickDown;
        ButtonState leftStickLeft;
        ButtonState leftStickRight;

        ButtonState rightStickUp;
        ButtonState rightStickDown;
        ButtonState rightStickLeft;
        ButtonState rightStickRight;

        ButtonState leftTrigger;
        ButtonState rightTrigger;

#pragma prefast(suppress: 26495, "Reset() performs the initialization")
        ButtonStateTracker() { Reset(); }

        void __cdecl Update(const State& state);

        void __cdecl Reset();

        State __cdecl GetLastState() const { return lastState; }

    private:
        State lastState;
    };

public:
    State GetState(const DWORD index);
};
