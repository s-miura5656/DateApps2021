#pragma once
#include"../../../ESGLib.h"

class UiManager
{
private:


public:
    UiManager();
    ~UiManager();


    void Initialize();
    void Update();
    void Draw();

    FONT time_limit_font;
};