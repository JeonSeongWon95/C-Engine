#pragma once
#include "WGameObject.h"

namespace Won
{
    class Mushroom :
        public WGameObject
    {
    public:
        Mushroom();
        ~Mushroom();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

    private:
        float mIsInit;
    };
}

