#pragma once
#include "Component.h"


namespace Won
{
	class SpriteRenderComponent : public Component
	{
	public:
		SpriteRenderComponent();
		~SpriteRenderComponent();


		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;

	private:
	};
}

