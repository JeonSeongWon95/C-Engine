#pragma once
#include "WScript.h"


namespace Won
{
    class WCameraScript : public WScript
    {
    public:
        WCameraScript();
        ~WCameraScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        void OnColliderEnter(WCollider* Other) override;
        void OnColliderStay(WCollider* Other) override;
        void OnColliderExit(WCollider* Other) override;
    };
}
