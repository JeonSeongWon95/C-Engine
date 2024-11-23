#pragma once
#include "WComponent.h"

namespace Won
{
    class WCamera : public WComponent
    {
    public:
        Vector2 CaluatePostion(Vector2 pos) { return pos - mDistance; }
        Vector2 CaluateTilePosition(Vector2 pos) { return pos + mDistance; }
         
        WCamera();
        ~WCamera();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
        void SetTarget(WGameObject* Target) { mTarget = Target; }


    private:
        WGameObject* mTarget;
        Vector2 mDistance;
        Vector2 mLookPosition;
        Vector2 mResolution;

    };
}

