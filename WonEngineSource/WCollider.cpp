#include "WCollider.h"
#include "WGameObject.h"
#include "WScript.h"

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
	WScript*  otherscript = Other->GetOwner()->GetComponent<WScript>();
	WScript* thisscript = GetOwner()->GetComponent<WScript>();

	otherscript->OnColliderEnter(this);
	thisscript->OnColliderEnter(Other);
	
}

void Won::WCollider::OnColliderStay(WCollider* Other)
{
	WScript* otherscript = Other->GetOwner()->GetComponent<WScript>();
	WScript* thisscript = GetOwner()->GetComponent<WScript>();

	otherscript->OnColliderStay(this);
	thisscript->OnColliderStay(Other);
}

void Won::WCollider::OnColliderExit(WCollider* Other)
{
	WScript* otherscript = Other->GetOwner()->GetComponent<WScript>();
	WScript* thisscript = GetOwner()->GetComponent<WScript>();

	otherscript->OnColliderExit(this);
	thisscript->OnColliderExit(Other);
}
