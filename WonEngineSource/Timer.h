#pragma once
#include "includeHeader.h"


namespace Won
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		static void Initialize();
		static void Update();
		static void Render(HDC NewDC);
		static float GetDeltaSeconds() { return DeltaSeconds; }

	private:
		static LARGE_INTEGER TotalFrequency;
		static LARGE_INTEGER CurrentFrequency;
		static LARGE_INTEGER PreFrequency;

		static float DeltaSeconds;


	};
}

