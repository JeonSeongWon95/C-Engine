#pragma once
#include "WGameObject.h"

namespace Won
{
    class TileObject : public WGameObject
    {
    public:
        TileObject();
        ~TileObject();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

    };
}

