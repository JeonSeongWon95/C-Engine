#pragma once
#include "Entry.h"

namespace Won
{
    class WResource : public Entry
    {

    public:
        WResource(eResourceType NewType);
        virtual ~WResource();

        virtual HRESULT Load(const std::wstring& NewPath) = 0;
        void SetPath(const std::wstring& NewPath) { Path = NewPath; }
        std::wstring& GetPath() { return Path; }

    private:
        eResourceType Type;
        std::wstring Path;

    };

}

