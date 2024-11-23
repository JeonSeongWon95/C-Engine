#pragma once
#include "Entry.h"
#include "includeHeader.h"

namespace Won
{
    class WUIBase : public Entry
    {
    public:
        WUIBase();
        virtual ~WUIBase();

        void Initialize();
        void Active();
        void Update();
        void LateUpdate();
        void Render(HDC NewDC);
        void UIClear();

        bool IsFullScreen() { return mIsFullScreen; }
        void IsActive();
        void SetActive(bool NewBool) { mEnable = NewBool; }
        void SetIsFullScreen(bool NewBool) { mIsFullScreen = NewBool; }
        void SetSize(Vector2 NewSize) { mSize = NewSize; }
        void SetUIType(eUIType type) { mType = type; }
        void SetPosition(Vector2 NewPosition) { mPosition = NewPosition; }
        eUIType GetUIType() { return mType; }

        virtual void OnActive();
        virtual void OnIsActive();
        virtual void OnInit();
        virtual void OnUpdate();
        virtual void OnLateUpdate();
        virtual void OnRender(HDC NewDC);
        virtual void Onclear();

    protected:
        Vector2 mPosition;
        Vector2 mSize;

    private:
        bool mIsFullScreen;
        bool mEnable;
        eUIType mType;
        
    };
}

