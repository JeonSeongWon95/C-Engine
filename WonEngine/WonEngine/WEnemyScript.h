#pragma once
#include "WScript.h"

namespace Won
{
    class WEnemyScript : public WScript
    {
    public:
        enum eEnemyState
        {
            IdleState,
            WalkState
        };

        WEnemyScript();
        virtual ~WEnemyScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        void OnColliderEnter(WCollider* Other) override;
        void OnColliderStay(WCollider* Other) override;
        void OnColliderExit(WCollider* Other) override;

        void Idle();
        void Walk();
        void Dead();

    private:
        eEnemyState mState;
        eDirection Direction;
        class WAnimator* Anim;
        float mTimer;
        float mDeathTimer;

    };
}

