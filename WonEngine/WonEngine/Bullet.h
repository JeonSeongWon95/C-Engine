#pragma once
#include "WGameObject.h"


namespace Won
{
    class Bullet : public WGameObject
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

