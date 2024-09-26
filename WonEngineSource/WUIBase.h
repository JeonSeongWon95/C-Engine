#pragma once
#include "Entry.h"
#include "includeHeader.h"

namespace Won
{
    class WUIBase : public Entry
    {
    public:
        WUIBase();
        ~WUIBase();

        void Initialize();
        void Active();
        void Update();
        void LateUpdate();
        void Render(HDC NewDC);
        void UIClear();

        bool IsFullScreen() { return mIsFullScreen; }
        void IsActive() { mEnable = false; }
        void SetActive(bool NewBool) { mEnable = NewBool; }
        void SetIsFullScreen(bool NewBool) { mIsFullScreen = NewBool; }
        eUIType GetUIType() { return mType; }

    private:
        bool mIsFullScreen;
        bool mEnable;
        eUIType mType;
        
    };
}

