#pragma once
#include "WUIBase.h"

namespace Won
{
    class WScore : public WUIBase
    {
    public:
        WScore();
        ~WScore();

        void OnActive() override;
        void OnIsActive() override;
        void OnInit() override;
        void OnUpdate() override;
        void OnLateUpdate() override;
        void OnRender(HDC NewDC) override;
        void Onclear() override;

        void AddScore(UINT NewScore) { mScore += NewScore; }

    private:
        UINT mScore;

    };
}

