#pragma once
#include "Component.h"

namespace Won
{
    class WCamera : public Component
    {
    public:
        FVector2 CaluatePostion(FVector2 pos) { return pos - mDistance; }
         
        WCamera();
        ~WCamera();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;


    private:
        GameObject* Target;
        FVector2 mDistance;
        FVector2 mLookPosition;
        FVector2 mResolution;

    };
}

