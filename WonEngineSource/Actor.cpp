#include "Actor.h"

Won::Actor::Actor()
	: aX(0.0f)
	, aY(0.0f)
{
}

Won::Actor::~Actor()
{
}

void Won::Actor::Initialize()
{
}

void Won::Actor::Run()
{
}

void Won::Actor::Update()
{
	if (GetAsyncKeyState('A') & 0X8000)
	{
		aX -= 0.01f;
	}
	if (GetAsyncKeyState('D') & 0X8000)
	{
		aX += 0.01f;
	}
	if (GetAsyncKeyState('W') & 0X8000)
	{
		aY -= 0.01f;
	}
	if (GetAsyncKeyState('S') & 0X8000)
	{
		aY += 0.01f;
	}
}

void Won::Actor::LateUpdate()
{
}

void Won::Actor::Render(HDC NewDC)
{
	HBRUSH RedBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH OldBrush = (HBRUSH)SelectObject(NewDC, RedBrush);

	Rectangle(NewDC, static_cast<int>(500 + aX), static_cast<int>(500 + aY), static_cast<int>(600 + aX), static_cast<int>(600 + aY));

	SelectObject(NewDC, OldBrush);
	DeleteObject(RedBrush);

}
