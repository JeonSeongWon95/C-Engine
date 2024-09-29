#pragma once
#include "WGameObject.h"

namespace Won
{
    class ItemBlock : public WGameObject
    {
    public:
        ItemBlock();
        ~ItemBlock();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;
    };
}

