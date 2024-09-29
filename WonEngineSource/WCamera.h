#pragma once
#include "WComponent.h"

namespace Won
{
    class WCamera : public WComponent
    {
    public:
        sVector2<float> CaluatePostion(sVector2<float> pos) { return pos - mDistance; }
        sVector2<float> CaluateTilePosition(sVector2<float> pos) { return pos + mDistance; }
         
        WCamera();
        ~WCamera();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
        void SetTarget(WGameObject* Target) { mTarget = Target; }


    private:
        WGameObject* mTarget;
        sVector2<float> mDistance;
        sVector2<float> mLookPosition;
        sVector2<float> mResolution;

    };
}

