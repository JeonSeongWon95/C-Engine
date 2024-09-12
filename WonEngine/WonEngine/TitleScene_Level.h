#pragma once
#include "../WonEngineSource/Scene_Level.h"


namespace Won
{
    class TitleScene_Level : public Scene_Level
    {
    public:
        TitleScene_Level();
        ~TitleScene_Level();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
        void OnEnter() override;
        void OnExit() override;
    };
}

