#pragma once
#include "WScene.h"

namespace Won
{
    class WDontDestoryScene : public WScene
    {
	public:
		WDontDestoryScene();
		~WDontDestoryScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;

    };
}

