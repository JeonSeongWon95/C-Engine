#pragma once
#include "Collider.h"


namespace Won
{
    class SphereCollider2D : public Collider
    {
	public:
		SphereCollider2D();
		~SphereCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;

	private:
    };
}

