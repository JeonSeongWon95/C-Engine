#pragma once
#include "GameObject.h"


namespace Won
{
    class Bullet : public GameObject
    {
    public:
        Bullet();
        ~Bullet();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render(HDC NewDC);

    };
}

