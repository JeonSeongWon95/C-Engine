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

        void AddForce(Vector2 NewForce) { mforce = NewForce; }
        void Setmass(float NewMass) { mmass = NewMass; }
        void SetIsGround(bool Newbool) { mIsGround = Newbool; }
        void SetVelocity(Vector2 NewVelocity) { mVeolcity = NewVelocity; }
        bool IsGround() { return mIsGround; }
        Vector2 GetVelocity() { return mVeolcity; }
        

    private:
        bool mIsGround;
        float mmass;
        float mfriction;

       Vector2 mforce;
       Vector2 mAcceleration;
       Vector2 mVeolcity;
       Vector2 mLimitedVelocity;
       Vector2 mGravity;
    };
}

