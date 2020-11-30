#pragma once
#include"../../../ESGLib.h"
#include "../ManagerBase.h"

class BaseUi;

class MainUiManager : public ManagerBase
{
public:
    //! @enum ÉVÅ[Éìñº
    enum UiState
    {
        TITLE,
        MAIN,
        RESULT
    };

    MainUiManager();
    ~MainUiManager();

    bool Initialize() override;
    int Update() override;
    void Draw2D() override;
    void Draw3D() override {}

private:
    BaseUi*_ui;
};