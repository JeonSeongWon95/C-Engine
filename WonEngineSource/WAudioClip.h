#pragma once
#include "WFmod.h"
#include "WResource.h"

namespace Won
{
    class WAudioClip : public WResource
    {
    public:
        WAudioClip();
        ~WAudioClip();

        HRESULT Load(const std::wstring& NewPath) override;

    private:
        FMOD::Sound* mSound;
        FMOD::Channel* mChannel;
    };
}

