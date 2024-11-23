#include "WFlagBlockScript.h"
#include "WCollider.h"
#include "WGameObject.h"
#include "WPlayerScript.h"
#include "WonObject.h"
#include "WTransform.h"
#include "WTime.h"
#include "WHUD.h"
#include "WRigidbody.h"

Won::WFlagBlockScript::WFlagBlockScript()
{
}

Won::WFlagBlockScript::~WFlagBlockScript()
{
}

void Won::WFlagBlockScript::Initialize()
{
}

void Won::WFlagBlockScript::Update()
{
}

void Won::WFlagBlockScript::LateUpdate()
{
}

void Won::WFlagBlockScript::Render(HDC NewDC)
{
}

void Won::WFlagBlockScript::OnColliderEnter(WCollider* Other)
{
	WPlayerScript* PlayerScript = Other->GetOwner()->GetComponent<WPlayerScript>();

	if (PlayerScript == nullptr)
		return;

	WTransform* PlayerTr = Other->GetOwner()->GetComponent<WTransform>();
	WRigidbody* PlayerRB = Other->GetOwner()->GetComponent<WRigidbody>();
	WTransform* FloorTr = GetOwner()->GetComponent<WTransform>();

	WCollider* FloorCollider = GetOwner()->GetComponent<WCollider>();
	Vector2 PlayerPos = PlayerTr->GetPosition();
	Vector2 FloorPos = FloorTr->GetPosition();

	float PlayerPosMaxY = PlayerPos.y + Other->GetSize().y;
	float FloorPosMaxY = FloorPos.y + FloorCollider->GetSize().y;
	float PlayerPosMaxX = PlayerPos.x + Other->GetSize().x;
	float FloorPosMaxX = FloorPos.x + FloorCollider->GetSize().x;
	float PlayerPosMinY = PlayerPos.y;
	float FloorPosMinY = FloorPos.y;
	float PlayerPosMinX = PlayerPos.x;
	float FloorPosMinX = FloorPos.x;

	float PlayerVelocityX = PlayerRB->GetVelocity().x;
	float PlayerVelocityY = PlayerRB->GetVelocity().y;

	float overlapX = min(PlayerPosMaxX, FloorPosMaxX) - max(PlayerPosMinX, FloorPosMinX);
	float overlapY = min(PlayerPosMaxY, FloorPosMaxY) - max(PlayerPosMinY, FloorPosMinY);

	if (overlapX < overlapY)
	{

		if (PlayerVelocityX > 0)
		{
			PlayerPos.x = FloorPosMinX - (PlayerPosMaxX - PlayerPosMinX);
		}
		else if (PlayerVelocityX < 0)
		{
			PlayerPos.x = FloorPosMaxX;
		}

		PlayerVelocityX = 0;
	}
	else
	{
		if (PlayerVelocityY > 0)
		{
			PlayerRB->SetIsGround(true);
			PlayerPos.y = FloorPosMinY - (PlayerPosMaxY - PlayerPosMinY);
			WHUD::AddScore(1000);
			PlayerScript->WalkRight();
			return;
		}

		PlayerVelocityY = 0;
	}

	PlayerTr->SetPos(PlayerPos);
	PlayerRB->SetVelocity(Vector2(PlayerVelocityX, PlayerVelocityY));
}

void Won::WFlagBlockScript::OnColliderStay(WCollider* Other)
{
}

void Won::WFlagBlockScript::OnColliderExit(WCollider* Other)
{
	WRigidbody* PlayerRB = Other->GetOwner()->GetComponent<WRigidbody>();
	PlayerRB->SetIsGround(false);
}
