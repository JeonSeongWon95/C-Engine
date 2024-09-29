#pragma once
#include "../WonEngineSource/WScene.h"

namespace Won
{
	class WPlayScene : public WScene
	{
	public:
		WPlayScene();
		~WPlayScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;
		void OnEnter() override;
		void OnExit() override;

	private:
		class Player* mCharacter;
		class WCamera* mMainCamera;
	};
}

