#pragma once
#include "WComponent.h"


namespace Won
{
    class WCollider : public WComponent
    {
    public:

        enum class eColliderType
        {
            None,
            Box,
            Sphere

        };

        WCollider();
        ~WCollider();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        virtual void OnColliderEnter(WCollider* Other);
        virtual void OnColliderStay(WCollider* Other);
        virtual void OnColliderExit(WCollider* Other);

        sVector2<float> GetOffset() { return offset; }
        void Setoffset(sVector2<float> NewOffset) { offset = NewOffset; }
        UINT32 GetID() { return mID; }
        void SetSize(sVector2<float> NewSize) { mSize = NewSize; }
        sVector2<float> GetSize() { return mSize; }
        eColliderType GetColliderType() { return mType; }
        void SetColliderType(eColliderType NewType) { mType = NewType; }

    private:
        static UINT32 ColliderID;
        sVector2<float> offset;
        sVector2<float> mSize;
        eColliderType mType;
        UINT32 mID;
    };
}

