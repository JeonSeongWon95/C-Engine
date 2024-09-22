#include "Collider.h"

UINT32 Won::Collider::ColliderID = 1;

Won::Collider::Collider()
	:Component(eComponentType::Collider)
	,offset(0,0)
	,mID(ColliderID++)
{

}

Won::Collider::~Collider()
{
}

void Won::Collider::Initialize()
{
}

void Won::Collider::Update()
{
}

void Won::Collider::LateUpdate()
{
}

void Won::Collider::Render(HDC NewDC)
{
}

void Won::Collider::OnColliderEnter(Collider* Other)
{
}

void Won::Collider::OnColliderStay(Collider* Other)
{
}

void Won::Collider::OnColliderExit(Collider* Other)
{
}
