#pragma once
#include "WComponent.h"

namespace Won
{
    class WRigidbody : public WComponent
    {
    public:
        WRigidbody();
        virtual ~WRigidbody();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render(HDC NewDC) override;

    private:
        float mmass;
        float mfriction;

        sVector2<float> mforce;
        sVector2<float> mAcceleration;
        sVector2<float> mVeolcity;
    };
}

