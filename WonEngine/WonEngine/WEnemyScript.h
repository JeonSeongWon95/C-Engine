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

        enum eEnemyDirection
        {
            LEFT,
            RIGHT
        };

        WEnemyScript();
        virtual ~WEnemyScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        void Idle();
        void Walk();

    private:
        eEnemyState mState;
        eEnemyDirection Direction;
        class WAnimator* Anim;
        float mTimer;
        float mDeathTimer;

    };
}
