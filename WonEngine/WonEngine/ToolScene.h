#pragma once
#include "../WonEngineSource/WScene.h"


namespace Won
{
    class ToolScene : public WScene
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

		static Won::Vector2 sStartPosition;


	private:
    };
}

LRESULT CALLBACK WndProcToo(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

