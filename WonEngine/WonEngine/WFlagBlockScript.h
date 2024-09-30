#pragma once
#include "WScript.h"

namespace Won
{
    class WFlagBlockScript : public WScript
    {
    public:
        WFlagBlockScript();
        ~WFlagBlockScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        void OnColliderEnter(WCollider* Other) override;
        void OnColliderStay(WCollider* Other) override;
        void OnColliderExit(WCollider* Other) override;

    };
}

