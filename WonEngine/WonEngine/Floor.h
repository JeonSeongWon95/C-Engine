#pragma once
#include "WGameObject.h"

namespace Won
{
    class Floor : public WGameObject
    {
    public:
        Floor();
        ~Floor();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
    };
}

