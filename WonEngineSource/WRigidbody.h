#pragma once
#include "WComponent.h"

namespace Won
{
    class WRigidbody : public WComponent
    {
    public:
        WRigidbody();
        ~WRigidbody();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        void AddForce(sVector2<float> NewForce) { mforce = NewForce; }
        void Setmass(float NewMass) { mmass = NewMass; }
        void SetIsGround(bool Newbool) { mIsGround = Newbool; }
        void SetVelocity(sVector2<float> NewVelocity) { mVeolcity = NewVelocity; }
        bool IsGround() { return mIsGround; }
        sVector2<float> GetVelocity() { return mVeolcity; }
        

    private:
        bool mIsGround;
        float mmass;
        float mfriction;

        sVector2<float> mforce;
        sVector2<float> mAcceleration;
        sVector2<float> mVeolcity;
        sVector2<float> mLimitedVelocity;
        sVector2<float> mGravity;
    };
}

