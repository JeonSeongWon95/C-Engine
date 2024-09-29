#pragma once
#include "../WonEngineSource/WScript.h"

namespace Won
{
    class WPlayerScript : public WScript
    {
    public:
        enum ePlayerState
        {
            IdleState,
            WalkState,
            JumpState,
            AttackState,
        };

        enum ePlayerSize
        {
            Small,
            Bigger
        };

        WPlayerScript();
        virtual ~WPlayerScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        void OnColliderEnter(WCollider* Other) override;
        void OnColliderStay(WCollider* Other) override;
        void OnColliderExit(WCollider* Other) override;

        void Idle();
        void Walk();
        void Jump();
        void Change();
        void Fire();
        void AddDamage();
        void AddDamageEnd();
        void Dead();

        eDirection GetPlayerDirection() { return Direction ;}
        ePlayerSize GetPlayerSize() { return Size; }

    private:
        ePlayerState mState;
        eDirection Direction;
        ePlayerSize Size;
        class WAnimator* Anim;
        UINT mPlayerHealth;
        bool mPlayerIsHit;
        float mHitTimer;
        float mDeadTimer;
        bool mIsBigger;
    };
}

