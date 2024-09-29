#pragma once
#include "WScript.h"

namespace Won
{
    class WSelectScript : public WScript
    {
    public:
        enum class eSelectedOption
        {
            None,
            PlayerOne,
            PlayerTwo,
            End
        };
        WSelectScript();
        ~WSelectScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

    private:
        eSelectedOption mPresentSelected;
    };
    
}

