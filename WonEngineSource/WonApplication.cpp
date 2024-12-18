#include "WonApplication.h"
#include "WInput.h"
#include "WTime.h"
#include "WSceneManager.h"
#include "WColliderManager.h"
#include "WUIManager.h"
#include "WFmod.h"
#include "WResourceManager.h"

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

		mGraphicDevice = std::make_unique<WGraphicDevice_DX11>();


		WFmod::Initialize();
		WColliderManager::Initialize();
		WUIManager::Initialize();
		WSceneManager::Initialize();
	}

	void WonApplication::Run()
	{
		Update();
		LateUpdate();
		Render();
		Destroy();
	}
	void WonApplication::Update()
	{
		WTime::Update();
		WColliderManager::Update();
		WUIManager::Update();
		WInput::Update();
		WSceneManager::Update();
	}

	void WonApplication::LateUpdate()
	{
		WColliderManager::LateUpdate();
		WUIManager::LateUpdate();
		WSceneManager::LateUpdate();
	}

	void WonApplication::Render()
	{
		ClearBuffer();

		WTime::Render(shdc);
		WColliderManager::Render(shdc);
		WSceneManager::Render(shdc);
		WUIManager::Render(shdc);
		//Pos 재설정 추가
		CopyBuffer(shdc, ahdc);
	}
	void WonApplication::Destroy()
	{
		WSceneManager::Destroy();
	}
	void WonApplication::Release()
	{
		WSceneManager::Release();
		WResourceManager::Release();
		WUIManager::Release();
	}

	void WonApplication::ClearBuffer()
	{
		HBRUSH GrayBrush = CreateSolidBrush(RGB(124, 134, 255));
		HBRUSH OldBrush = (HBRUSH)SelectObject(shdc, GrayBrush);

		::Rectangle(shdc, -1, -1, Width + 1, Height + 1);
		(HBRUSH)SelectObject(shdc, OldBrush);

		DeleteObject(GrayBrush);
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

		SetWindowPos(ahwnd, nullptr, 0, 0, Width, Height, 0);
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
		WInput::Initialize();
		WTime::Initialize();
	}
}