#pragma once
#include "WGameObject.h"

namespace Won
{
    class WFlagBlock : public WGameObject
    {
    public:
        WFlagBlock();
        ~WFlagBlock();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
    };
}

