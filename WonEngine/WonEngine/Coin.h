#pragma once
#include "WGameObject.h"


namespace Won
{
    class Coin : public WGameObject
    {
    public:
        Coin();
        ~Coin();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
    };
}

