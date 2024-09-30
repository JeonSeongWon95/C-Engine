#include "WFlagScript.h"
#include "WCollider.h"
#include "WGameObject.h"
#include "WPlayerScript.h"
#include "WonObject.h"
#include "WTransform.h"
#include "WTime.h"
#include "WHUD.h"
#include "WRigidbody.h"

Won::WFlagScript::WFlagScript()
	:mIsPickup(false)
{
}

Won::WFlagScript::~WFlagScript()
{
}

void Won::WFlagScript::Initialize()
{

}

void Won::WFlagScript::Update()
{

}

void Won::WFlagScript::LateUpdate()
{
}

void Won::WFlagScript::Render(HDC NewDC)
{
}

void Won::WFlagScript::OnColliderEnter(WCollider* Other)
{
	WPlayerScript* PlayerScript = Other->GetOwner()->GetComponent<WPlayerScript>();

	if (PlayerScript == nullptr)
		return;

	PlayerScript->PickUpflag();
}

void Won::WFlagScript::OnColliderStay(WCollider* Other)
{
}

void Won::WFlagScript::OnColliderExit(WCollider* Other)
{

}

