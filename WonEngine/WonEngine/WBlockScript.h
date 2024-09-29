#pragma once
#include "WScript.h"
#include "includeHeader.h"

namespace Won
{
    class WBlockScript : public WScript
    {
    public:
        WBlockScript();
        ~WBlockScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        void OnColliderEnter(WCollider* Other) override;
        void OnColliderStay(WCollider* Other) override;
        void OnColliderExit(WCollider* Other) override;

    private:
        bool mIsHit;
        float mStartposition;
    };
}

