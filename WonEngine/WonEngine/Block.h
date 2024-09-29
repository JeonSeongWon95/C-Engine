#pragma once
#include "WGameObject.h"



namespace Won
{
    class Block : public WGameObject
    {
    public:
        Block();
        ~Block();

       void Initialize() override;
       void Update() override;
       void LateUpdate() override;
       void Render(HDC NewDC) override;
    };
}

