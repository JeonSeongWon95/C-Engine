#pragma once
#include "../WonEngineSource/Scene_Level.h"


namespace Won
{
    class ToolScene : public Scene_Level
    {
	public:
		ToolScene();
		~ToolScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;
		void OnEnter() override;
		void OnExit() override;

		void Load();
		void Save();

		static Won::mVector2<int> sStartPosition;


	private:
    };
}

LRESULT CALLBACK WndProcToo(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

