#pragma once
#include "../WonEngineSource/WScene.h"


namespace Won
{
    class WTitleScene : public WScene
    {
    public:
        WTitleScene();
        ~WTitleScene();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
        void OnEnter() override;
        void OnExit() override;
    };
}

