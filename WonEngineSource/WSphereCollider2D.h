#pragma once
#include "WCollider.h"


namespace Won
{
    class WSphereCollider2D : public WCollider
    {
	public:
		WSphereCollider2D();
		~WSphereCollider2D();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC NewDC) override;

		void OnColliderEnter(WCollider* Other) override;
		void OnColliderStay(WCollider* Other) override;
		void OnColliderExit(WCollider* Other) override;

	private:
    };
}

