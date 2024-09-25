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

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render(HDC NewDC) override;

        void SetPlayer(class Player* NewPlayer) { Target = NewPlayer; }
        void SetTargetPos(sVector2<float> NewPos) { Pos = NewPos; }


    private:
        Player* Target;
        sVector2<float> Pos;
        WPlayerScript::ePlayerDirection Dr;
        float mDeathTimer;
    };
}

