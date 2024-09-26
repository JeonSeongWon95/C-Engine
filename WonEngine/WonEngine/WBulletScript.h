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
        void SetTargetPos(sVector2<float> NewPos) { Pos = NewPos; }

        void OnColliderEnter(WCollider* Other) override;
        void OnColliderStay(WCollider* Other) override;
        void OnColliderExit(WCollider* Other) override;


    private:
        Player* Target;
        sVector2<float> Pos;
        WPlayerScript::ePlayerDirection Dr;
        float mDeathTimer;
    };
}

