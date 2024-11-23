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

	Vector2 PlayerPos = playerTr->GetPosition();
	Vector2 FloorPos = floorTr->GetPosition();

	float len = (FloorPos.y - PlayerPos.y) + 10;
	float scale = playerCol->GetSize().y;

	if (len < scale)
	{
		float Distance = fabs((PlayerPos.y + Other->GetSize().y) - FloorPos.y);
		PlayerPos.y -= Distance;
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
