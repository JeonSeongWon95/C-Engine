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
            ChangeSize
        };

        enum ePlayerDirection
        {
            LEFT,
            RIGHT
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
        void Dead();

        ePlayerDirection& GetPlayerDirection() { return Direction ;}

    private:
        ePlayerState mState;
        ePlayerDirection Direction;
        ePlayerSize Size;
        class WAnimator* Anim;
        UINT mPlayerHealth;
        bool mPlayerIsHit;
        float mHitTimer;

    };
}

