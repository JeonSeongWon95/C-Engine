#pragma once
#include "WScene.h"

namespace Won
{
    class DontDestoryScene : public WScene
    {
	public:
		DontDestoryScene();
		~DontDestoryScene();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;

    };
}

