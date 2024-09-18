#pragma once
#include "includeHeader.h"


namespace Won
{
	class Entry
	{
	public:
		Entry();
		virtual ~Entry();

		void SetName(const std::wstring& NewName) { Name = NewName; }
		std::wstring GetName() { return Name; }

	protected:
		std::wstring Name;
		
	};
}

