#pragma once
#include "Component.h"

namespace Won
{
    class WAnimator :  public Component
    {
    public:
        WAnimator();
        ~WAnimator();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

        class WAnimation* CreateAnimation(std::wstring& Name, mVector2<float> StartPosition, mVector2<float> SpriteSize, mVector2<float> offset,
            mVector2<float>  , bool AnimationCompleted);

        WAnimation* FindAnimation(std::wstring& Name);


    private:
       std::map<std::wstring, WAnimation*> Animations;
       WAnimation* ActiveAnimation;
       bool mLoop;
    };
}

