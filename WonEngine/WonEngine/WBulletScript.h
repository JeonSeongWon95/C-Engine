#pragma once
#include "WScript.h"
#include "WPlayerScript.h"


namespace Won
{
    class WBulletScript : public WScript
    {
    public:
        WBulletScript();
        ~WBulletScript();

       void Initialize() override;
       void Update() override;
       void LateUpdate() override;
       void Render(HDC NewDC) override;

        void SetPlayer(class Player* NewPlayer) { Target = NewPlayer; }
        void SetTargetPos(Vector2 NewPos) { Pos = NewPos; }

        void OnColliderEnter(WCollider* Other) override;
        void OnColliderStay(WCollider* Other) override;
        void OnColliderExit(WCollider* Other) override;


    private:
        Player* Target;
        Vector2 Pos;
        eDirection Dr;
        float mDeathTimer;
    };
}

