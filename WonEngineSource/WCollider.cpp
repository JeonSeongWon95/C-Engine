#include "WCollider.h"

UINT32 Won::WCollider::ColliderID = 1;

Won::WCollider::WCollider()
	:WComponent(eComponentType::WCollider)
	,offset(0,0)
	,mID(ColliderID++)
	,mType(eColliderType::None)
{

}

Won::WCollider::~WCollider()
{
}

void Won::WCollider::Initialize()
{
}

void Won::WCollider::Update()
{
}

void Won::WCollider::LateUpdate()
{
}

void Won::WCollider::Render(HDC NewDC)
{
}

void Won::WCollider::OnColliderEnter(WCollider* Other)
{
}

void Won::WCollider::OnColliderStay(WCollider* Other)
{
}

void Won::WCollider::OnColliderExit(WCollider* Other)
{
}
