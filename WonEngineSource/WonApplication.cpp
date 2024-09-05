#include "WonApplication.h"
#include "Input.h"
#include "Timer.h"
#include "Scene_LevelManager.h"

namespace Won
{

	WonApplication::WonApplication()
		: ahwnd(nullptr)
		, ahdc(nullptr)
		, shdc(nullptr)
		, BackBuffer(nullptr)
		, Speed(0.0f)
		, Width(0)
		, Height(0)
	{

	}

	WonApplication::~WonApplication()
	{
	}

	void WonApplication::Initialize(HWND NewHWND, int NewWidth, int NewHeight)
	{
		abjustwindowRect(NewHWND, NewWidth, NewHeight);
		createBuffer(NewWidth, NewHeight);

		initializeEtc();
		Scene_LevelManager::Initialize();
	}

	void WonApplication::Run()
	{
		Update();
		LateUpdate();
		Render();
	}
	void WonApplication::Update()
	{
		Timer::Update();
		Input::Update();
		Scene_LevelManager::Update();
	}

	void WonApplication::LateUpdate()
	{
		Scene_LevelManager::LateUpdate();
	}

	void WonApplication::Render()
	{
		ClearBuffer();

		Timer::Render(shdc);
		Scene_LevelManager::Render(shdc);

		CopyBuffer(shdc, ahdc);
	}

	void WonApplication::ClearBuffer()
	{
		Rectangle(shdc, -1, -1, Width + 1, Height + 1);
	}

	void WonApplication::CopyBuffer(HDC src, HDC des)
	{
		BitBlt(des, 0, 0, Width, Height, src, 0, 0, SRCCOPY);
	}

	void WonApplication::abjustwindowRect(HWND hwnd, UINT width, UINT height)
	{
		ahwnd = hwnd;
		ahdc = GetDC(hwnd);

		RECT rect = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		Width = width;
		Height = height;

		SetWindowPos(ahwnd, nullptr, 100, 100, Width, Height, 0);
		ShowWindow(hwnd, true);

	}

	void WonApplication::createBuffer(UINT width, UINT height)
	{
		shdc = CreateCompatibleDC(ahdc);
		BackBuffer = CreateCompatibleBitmap(ahdc, width, height);

		HBITMAP BaseBuffer = (HBITMAP)SelectObject(shdc, BackBuffer);
		DeleteObject(BaseBuffer);
	}

	void WonApplication::initializeEtc() 
	{
		Input::Initialize();
		Timer::Initialize();
	}
}