#pragma once
#include "WScene.h"

namespace Won
{
    class DeadScene : public WScene
    {
	public:
		DeadScene();
		~DeadScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;
		void OnEnter() override;
		void OnExit() override;

    };
}

