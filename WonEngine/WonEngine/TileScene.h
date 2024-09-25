#pragma once
#include "../WonEngineSource/WScene.h"


namespace Won
{
    class TileScene : public WScene
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

