#pragma once
#include "WUIBase.h"

namespace Won
{
    class WTimer : public WUIBase
    {
    public:
        WTimer();
        ~WTimer();

        void OnActive() override;
        void OnIsActive() override;
        void OnInit() override;
        void OnUpdate() override;
        void OnLateUpdate() override;
        void OnRender(HDC NewDC) override;
        void Onclear() override;


    private:
        float mTime;
        int mRenderTime;
        float mOffset;
    };
}

