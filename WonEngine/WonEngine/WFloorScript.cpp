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
	WTransform* playerTr = Other->GetOwner()->GetComponent<WTransform>();
	WCollider* playerCol = Other;

	WRigidbody* floorRb = this->GetOwner()->GetComponent<WRigidbody>();
	WTransform* floorTr = this->GetOwner()->GetComponent<WTransform>();
	WCollider* floorCol = this->GetOwner()->GetComponent<WCollider>();

	sVector2<float> PlayerPos = playerTr->GetPosition();
	sVector2<float> FloorPos = floorTr->GetPosition();

	float len = (FloorPos.Y - PlayerPos.Y) + 10;
	float scale = playerCol->GetSize().Y;

	if (len < scale)
	{
		float Distance = fabs((PlayerPos.Y + Other->GetSize().Y) - FloorPos.Y);
		PlayerPos.Y -= Distance;
		playerTr->SetPos(PlayerPos);
	}

	PlayerRB->SetIsGround(true);

}

void Won::WFloorScript::OnColliderStay(WCollider* Other)
{
}

void Won::WFloorScript::OnColliderExit(WCollider* Other)
{
	WRigidbody* PlayerRB = Other->GetOwner()->GetComponent<WRigidbody>();
	PlayerRB->SetIsGround(false);
}
