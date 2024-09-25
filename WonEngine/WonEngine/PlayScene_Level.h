#pragma once
#include "../WonEngineSource/WScene.h"

namespace Won
{
	class PlayScene_Level : public WScene
	{
	public:
		PlayScene_Level();
		~PlayScene_Level();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;
		void OnEnter() override;
		void OnExit() override;

	private:
	};
}

