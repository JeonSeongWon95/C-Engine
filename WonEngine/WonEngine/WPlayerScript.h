#pragma once
#include "../WonEngineSource/WScript.h"

namespace Won
{
    class WPlayerScript : public WScript
    {
    public:
        WPlayerScript();
        virtual ~WPlayerScript();

        void Initialize() override;
        void Update() override;
        void LateUpdate() override;
        void Render(HDC NewDC) override;

    };
}

