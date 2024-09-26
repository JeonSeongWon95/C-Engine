#pragma once
#include "WComponent.h"

namespace Won
{
    class WAudioSource : public WComponent
    {
    public:
        WAudioSource();
        ~WAudioSource();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
    };
}

