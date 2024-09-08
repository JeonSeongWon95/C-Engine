#pragma once
#include "Component.h"

namespace Won
{
    class WScript : public Component
    {

    public:
        WScript();
        virtual ~WScript();

       virtual void Initialize() override;
       virtual void Update() override;
       virtual void LateUpdate() override;
       virtual void Render(HDC NewDC) override;

    };
}

