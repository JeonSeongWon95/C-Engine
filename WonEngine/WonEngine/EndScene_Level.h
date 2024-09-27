#pragma once
#include "../WonEngineSource/WScene.h"

namespace Won
{
    class EndScene_Level : public WScene
    {
    public:
        EndScene_Level();
        ~EndScene_Level();

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

