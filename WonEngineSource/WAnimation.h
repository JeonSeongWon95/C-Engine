#pragma once
#include "WResource.h"


namespace Won
{
    class WAnimation : public WResource
    {
    public:
        struct Sprite
        {
            mVector2<float> sStartPostion;
            mVector2<float> sSize;
        };

        WAnimation();
        ~WAnimation();

        virtual HRESULT Load(const std::wstring& NewPath) override;
        bool IsCompleted() { return bIsCompleted; }

        class WAnimation* CreateAnimation(std::wstring& Name, mVector2<float> StartPosition, mVector2<float> SpriteSize, mVector2<float> offset,
            mVector2<float>, bool AnimationCompleted);


    private:
        class WTexture* MainTexture;
        std::vector<Sprite> Sprites;
        UINT mIndex;
        bool bIsCompleted;

    };
}

