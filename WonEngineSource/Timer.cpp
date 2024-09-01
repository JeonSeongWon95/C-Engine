#include "Timer.h"

LARGE_INTEGER Won::Timer::TotalFrequency = {0, };
LARGE_INTEGER Won::Timer::CurrentFrequency = { 0, };
LARGE_INTEGER Won::Timer::PreFrequency = { 0, };
float Won::Timer::DeltaSeconds = 0;


Won::Timer::Timer()
{
}

Won::Timer::~Timer()
{
}

void Won::Timer::Initialize()
{
	QueryPerformanceFrequency(&TotalFrequency);
	QueryPerformanceCounter(&CurrentFrequency);
}

void Won::Timer::Update()
{
	PreFrequency.QuadPart = CurrentFrequency.QuadPart;
	QueryPerformanceCounter(&CurrentFrequency);
	DeltaSeconds = (static_cast<float>(CurrentFrequency.QuadPart - PreFrequency.QuadPart) / static_cast<float>(TotalFrequency.QuadPart));
}

void Won::Timer::Render(HDC NewDC)
{
	static float DeltaTime = 0;
	DeltaTime += DeltaSeconds;
	int CastDeltaTime = static_cast<int>(DeltaTime);
	wchar_t Clock[30] = {0,};

	swprintf(Clock, sizeof(Clock), L"%d", CastDeltaTime);
	TextOut(NewDC, 50, 10, Clock, (int)wcslen(Clock));

}
