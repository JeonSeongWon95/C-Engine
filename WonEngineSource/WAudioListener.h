#pragma once
#include "WComponent.h"

namespace Won
{
    class WAudioListener : public WComponent
    {
    public:
        WAudioListener();
        ~WAudioListener();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
    };
}

