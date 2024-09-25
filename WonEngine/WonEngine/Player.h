#pragma once
#include "WGameObject.h"

namespace Won
{
    class Player : public WGameObject
    {
    public:
        Player();
        ~Player();

      void Initialize() override;
      void Update() override;
      void LateUpdate() override;
      void Render(HDC NewDC) override;
    };
}

