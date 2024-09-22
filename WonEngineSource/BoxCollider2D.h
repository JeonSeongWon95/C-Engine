#pragma once
#include "Collider.h"


namespace Won
{
	class BoxCollider2D : public Collider
	{

	public:
		BoxCollider2D();
		~BoxCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;

	private:
	};
}
