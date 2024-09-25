#include "WTime.h"

LARGE_INTEGER Won::WTime::TotalFrequency = {0, };
LARGE_INTEGER Won::WTime::CurrentFrequency = { 0, };
LARGE_INTEGER Won::WTime::PreFrequency = { 0, };
float Won::WTime::DeltaSeconds = 0;


Won::WTime::WTime()
{
}

Won::WTime::~WTime()
{
}

void Won::WTime::Initialize()
{
	QueryPerformanceFrequency(&TotalFrequency);
	QueryPerformanceCounter(&CurrentFrequency);
}

void Won::WTime::Update()
{
	PreFrequency.QuadPart = CurrentFrequency.QuadPart;
	QueryPerformanceCounter(&CurrentFrequency);
	DeltaSeconds = (static_cast<float>(CurrentFrequency.QuadPart - PreFrequency.QuadPart) / static_cast<float>(TotalFrequency.QuadPart));
}

void Won::WTime::Render(HDC NewDC)
{
	static float DeltaTime = 0;
	DeltaTime += DeltaSeconds;
	int CastDeltaTime = static_cast<int>(DeltaTime);
	wchar_t Clock[30] = {0,};

	swprintf(Clock, sizeof(Clock), L"%d", CastDeltaTime);
	TextOut(NewDC, 50, 10, Clock, (int)wcslen(Clock));
}
