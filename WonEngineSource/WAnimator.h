#pragma once
#include "WComponent.h"

namespace Won
{
    class WAnimator :  public WComponent
    {
    public:
        struct Event
        {
            void operator=(std::function<void()> func)
            {
                mEvent = std::move(func);
            }

            void operator()()
            {
                if(mEvent)
                {
                    mEvent();
                }
            }

            std::function<void()> mEvent;
        };

        struct Events
        {
            Event mStartEvent;
            Event mCompleteEvent;
            Event mEndEvent;
        };
        

        WAnimator();
        ~WAnimator();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        void CreateAnimation(const std::wstring& Name, class WTexture* NewTexture, sVector2<float> StartPosition,
            sVector2<float> SpriteSize, sVector2<float> offset, UINT AnimationSize, float Duration, bool bIsReversal = false);

        class WAnimation* FindAnimation(const std::wstring& Name);
        Events* FindEvents(const std::wstring& Name);

        void PlayAnimation(const std::wstring& Name, bool bLoop);
        void SetRemoveColor(sVector3<int> Newcolor);
        bool IsCompletedActiveAnimation();
        Event& GetStartEvent(const std::wstring& Name);
        Event& GetCompleteEvent(const std::wstring& Name);
        Event& GetEndEvent(const std::wstring& Name);


    private:
       std::map<std::wstring, WAnimation*> mAnimations;
       std::map<std::wstring, Events*> mAnimEvents;
       WAnimation* mActiveAnimation;
       bool mLoop;
    };
}

