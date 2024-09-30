#pragma once
#include "WGameObject.h"

namespace Won
{
    class WWall : public WGameObject
    {
    public:
        WWall();
        ~WWall();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
    };
}

