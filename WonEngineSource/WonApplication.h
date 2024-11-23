#pragma once

#include "IncludeHeader.h"
#include "WGraphicDevice_DX11.h"

namespace Won
{
	class WonApplication
	{
	public:
		WonApplication();
		~WonApplication();

		void Initialize(HWND NewHWND, int NewWidth, int NewHeight);
		void Run();
		void Update();
		void LateUpdate();
		void Render();
		void Destroy();
		void Release();
		HDC GetEngineDC() { return ahdc; }
		HWND GetEngineWND() { return ahwnd; }
		int GetWidth() { return Width; }
		int GetHeight() { return Height; }

	private:

		void ClearBuffer();
		void CopyBuffer(HDC src, HDC des);
		void abjustwindowRect(HWND hwnd, UINT width, UINT height);
		void createBuffer(UINT width, UINT height);
		void initializeEtc();

		HWND ahwnd;
		HDC ahdc;
		HDC shdc;
		HBITMAP BackBuffer;
		std::unique_ptr<WGraphicDevice_DX11> mGraphicDevice;

		float Speed;
		int Width;
		int Height;

		

	protected:

	};

}



