#pragma once
#include "Entry.h"

namespace Won
{
    class WResource : public Entry
    {

    public:
        WResource(ResourceType NewType);
        virtual ~WResource();

        virtual HRESULT Load(const std::wstring& NewPath) = 0;
        void SetPath(std::wstring& NewPath) { Path = NewPath; }
        std::wstring& GetPath() { return Path; }

    private:
        ResourceType Type;
        std::wstring Path;

    };

}

