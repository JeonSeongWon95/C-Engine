#pragma once
#include "GameObject.h"

namespace Won
{
    class Player : public GameObject
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

