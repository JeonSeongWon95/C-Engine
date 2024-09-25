#pragma once
#include "WGameObject.h"

namespace Won
{
    class Enemy : public WGameObject
    {
    public:
        Enemy();
        ~Enemy();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
    };
}

