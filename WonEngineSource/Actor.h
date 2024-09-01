#pragma once
#include "includeHeader.h"

namespace Won
{
	class Actor
	{
	public:
		Actor();
		~Actor();

		void Initialize();
		void Run();
		void Update();
		void LateUpdate();
		void Render(HDC NewDC);

	protected:
		float aX;
		float aY;
	};
}

