#pragma once
#include "Component.h"


namespace Won
{
    class Collider : public Component
    {
    public:

        Collider();
        ~Collider();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        virtual void OnColliderEnter(Collider* Other);
        virtual void OnColliderStay(Collider* Other);
        virtual void OnColliderExit(Collider* Other);

        mVector2<float> GetOffset() { return offset; }
        void Setoffset(mVector2<float> NewOffset) { offset = NewOffset; }
        UINT32 GetID() { return mID; }
        void SetSize(mVector2<float> NewSize) { mSize = NewSize; }
        mVector2<float> GetSize() { return mSize; }

    private:
        static UINT32 ColliderID;
        mVector2<float> offset;
        mVector2<float> mSize;
        UINT32 mID;
    };
}

