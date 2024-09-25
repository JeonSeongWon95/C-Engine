#pragma once
#include "Component.h"

namespace Won
{
    class WCamera : public Component
    {
    public:
        mVector2<float> CaluatePostion(mVector2<float> pos) { return pos - mDistance; }
        mVector2<float> CaluateTilePosition(mVector2<float> pos) { return pos + mDistance; }
         
        WCamera();
        ~WCamera();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;


    private:
        GameObject* mTarget;
        mVector2<float> mDistance;
        mVector2<float> mLookPosition;
        mVector2<float> mResolution;

    };
}

