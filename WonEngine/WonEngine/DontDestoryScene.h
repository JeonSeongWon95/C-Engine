#pragma once
#include "Scene_Level.h"

namespace Won
{
    class DontDestoryScene : public Scene_Level
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

