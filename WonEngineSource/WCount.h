#pragma once
#include "WUIBase.h"

namespace Won {
    class WCount : public WUIBase
    {
    public:
        WCount();
        ~WCount();

        void OnActive() override;
        void OnIsActive() override;
        void OnInit() override;
        void OnUpdate() override;
        void OnLateUpdate() override;
        void OnRender(HDC NewDC) override;
        void Onclear() override;

        void AddCount(UINT NewScore);

    private:
        UINT mCount;
    };
}
