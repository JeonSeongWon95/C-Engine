#pragma once
#include "WScript.h"


namespace Won
{
    class WItemBlockScript : public WScript
    {

    public:
        WItemBlockScript();
        ~WItemBlockScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        void OnColliderEnter(WCollider* Other) override;
        void OnColliderStay(WCollider* Other) override;
        void OnColliderExit(WCollider* Other) override;

    private:
        bool mIsHit;
        bool mNoItem;
        bool mIsReset;
        float mStartposition;
        float mResetHit;
        eItemType mItem;
    };

};

