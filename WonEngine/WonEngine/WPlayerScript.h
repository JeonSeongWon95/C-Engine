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
            JumpState
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

        void Idle();
        void Walk();
        void Jump();
        void SpawnEnemy();


    private:
        ePlayerState mState;
        ePlayerDirection Direction;
        ePlayerSize Size;
        class WAnimator* Anim;

    };
}

