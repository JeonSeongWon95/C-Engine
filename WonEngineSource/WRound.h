#pragma once
#include "WUIBase.h"

namespace Won
{
    class WRound :
        public WUIBase
    {
    public:
        WRound();
        ~WRound();

        void OnActive() override;
        void OnIsActive() override;
        void OnInit() override;
        void OnUpdate() override;
        void OnLateUpdate() override;
        void OnRender(HDC NewDC) override;
        void Onclear() override;

    private:
        UINT mRound;

    };
}


