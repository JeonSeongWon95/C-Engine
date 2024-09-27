#pragma once
#include "WUIBase.h"

namespace Won
{
    class WHUD : public WUIBase
    {
    public:
        struct Number
        {
            sVector2<float> mSheetStartPosition;
            sVector2<float> mSize;
        };

        WHUD();
        ~WHUD();

        void OnActive() override;
        void OnIsActive() override;
        void OnInit() override;
        void OnUpdate() override;
        void OnLateUpdate() override;
        void OnRender(HDC NewDC) override;
        void Onclear() override;

        static Number* GetNumber(UINT Num) { if (Num > 9) { return nullptr; } return mNumbers[Num]; }
        static class WTexture* GetTexture() { return mNumberTexture; }


    private:
        static std::vector<Number*> mNumbers;
        std::vector<WUIBase*> mChildUI;
        static WTexture* mNumberTexture;
    };
}
