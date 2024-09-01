#pragma once
#include "../WonEngineSource/Scene_Level.h"

namespace Won
{
	class PlayScene_Level : public Scene_Level
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
		class Player* BG;
	};
}

