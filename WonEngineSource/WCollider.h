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

        Vector2 GetOffset() { return offset; }
        void Setoffset(Vector2 NewOffset) { offset = NewOffset; }
        UINT32 GetID() { return mID; }
        void SetSize(Vector2 NewSize) { mSize = NewSize; }
        Vector2 GetSize() { return mSize; }
        eColliderType GetColliderType() { return mType; }
        void SetColliderType(eColliderType NewType) { mType = NewType; }

    private:
        static UINT32 ColliderID;
        Vector2 offset;
        Vector2 mSize;
        eColliderType mType;
        UINT32 mID;
    };
}

