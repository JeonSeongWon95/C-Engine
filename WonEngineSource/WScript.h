#pragma once
#include "WComponent.h"

namespace Won
{
    class WScript : public WComponent
    {

    public:
        WScript();
        virtual ~WScript();

       void Initialize() override;
       void Update() override;
       void LateUpdate() override;
       void Render(HDC NewDC) override;

       virtual void OnColliderEnter(class WCollider* Other);
       virtual void OnColliderStay(WCollider* Other);
       virtual void OnColliderExit(WCollider* Other);

    };
}

