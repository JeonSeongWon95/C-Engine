#pragma once
#include "WResource.h"


namespace Won
{
    class WAnimation : public WResource
    {
    public:
        struct Sprite
        {
            Vector2 sStartPostion;
            Vector2 sSize;
            Vector2 Offset;
            float Duration;

            Sprite()
            {
                    sStartPostion = { 0,0 };
                    sSize = { 0,0 };
                    Duration = 0.0f;
                    Offset = { 0,0 };
            }
        };

        WAnimation();
        ~WAnimation();

        virtual HRESULT Load(const std::wstring& NewPath) override;
        bool IsCompleted() { return bIsCompleted; }
        void CreateAnimation(const std::wstring& Name, class WTexture* NewText, Vector2 StartPosition,
           Vector2 SpriteSize, Vector2 offset, UINT AnimationSize, float Duration, bool bIsReversal = false);

        void SetAnimator(class WAnimator* NewAnimator) { Animator = NewAnimator; }
        void Update();
        void Reset();
        void Render(HDC NewDC);
        void SetRemoveColor(Vector3 NewColor) { ColorKey = NewColor; }
      

    private:
        WAnimator* Animator;
        class WTexture* MainTexture;
        std::vector<Sprite*> Sprites;
        UINT mIndex;
        float mTimer;
        bool bIsCompleted;
        Vector3 ColorKey;

    };
}

