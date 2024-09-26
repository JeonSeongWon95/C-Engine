#pragma once
#include "WUIBase.h"

namespace Won
{
    class WButton : public WUIBase
    {
    public:
        struct Event
        {
            void operator=(std::function<void()> func)
            {
                OnClicked = std::move(func);
            }

            void operator()()
            {
                if (OnClicked)
                {
                    OnClicked();
                }
            }

            std::function<void()> OnClicked;
        };

        WButton();
        ~WButton();

        void OnActive() override;
        void OnIsActive() override;
        void OnInit() override;
        void OnUpdate() override;
        void OnLateUpdate() override;
        void OnRender(HDC NewDC) override;
        void Onclear() override;

        void OnClicked();

        Event* GetOnClickedEvent() { return &mOnClicked; }

    private:
        bool mIsOverlap;
        Event mOnClicked;
    };
}

