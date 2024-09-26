#include "WFloorScript.h"
#include "WCollider.h"
#include "WGameObject.h"
#include "WRigidbody.h"
#include "WTransform.h"

Won::WFloorScript::WFloorScript()
{
}

Won::WFloorScript::~WFloorScript()
{
}

void Won::WFloorScript::Initialize()
{
}

void Won::WFloorScript::Update()
{
}

void Won::WFloorScript::LateUpdate()
{
}

void Won::WFloorScript::Render(HDC NewDC)
{
}

void Won::WFloorScript::OnColliderEnter(WCollider* Other)
{
	
	WRigidbody* PlayerRB = Other->GetOwner()->GetComponent<WRigidbody>();
	PlayerRB->SetIsGround(true);

}

void Won::WFloorScript::OnColliderStay(WCollider* Other)
{
}

void Won::WFloorScript::OnColliderExit(WCollider* Other)
{
}
