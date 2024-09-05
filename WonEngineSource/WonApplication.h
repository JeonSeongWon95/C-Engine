#pragma once

#include "IncludeHeader.h"

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
		HDC GetEngineDC() { return ahdc; }

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

		float Speed;
		int Width;
		int Height;

		

	protected:

	};

}



