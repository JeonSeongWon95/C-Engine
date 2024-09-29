#pragma once
#include "../WonEngineSource/WScene.h"

namespace Won
{
    class WEndScene : public WScene
    {
    public:
        WEndScene();
        ~WEndScene();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
        void OnEnter() override;
        void OnExit() override;

    private:
        float mReStartTimer;
    };
}

