#pragma once
#include "GameObject.h"

namespace Won
{
    class Enemy : public GameObject
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

