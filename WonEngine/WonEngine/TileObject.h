#pragma once
#include "GameObject.h"

namespace Won
{
    class TileObject : public GameObject
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

