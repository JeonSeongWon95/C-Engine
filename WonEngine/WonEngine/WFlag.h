#pragma once
#include "WGameObject.h"

namespace Won
{
    class WFlag : public WGameObject
    {
    public:
        WFlag();
        ~WFlag();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
    };
}

