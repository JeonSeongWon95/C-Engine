#pragma once
#include "../WonEngineSource/Scene_Level.h"


namespace Won
{
    class TileScene : public Scene_Level
    {
	public:
		TileScene();
		~TileScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;
		void OnEnter() override;
		void OnExit() override;
    };
}

