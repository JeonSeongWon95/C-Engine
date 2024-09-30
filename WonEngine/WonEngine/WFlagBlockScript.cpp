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
	sVector2<float> PlayerPos = PlayerTr->GetPosition();
	sVector2<float> FloorPos = FloorTr->GetPosition();

	float PlayerPosMaxY = PlayerPos.Y + Other->GetSize().Y;
	float FloorPosMaxY = FloorPos.Y + FloorCollider->GetSize().Y;
	float PlayerPosMaxX = PlayerPos.X + Other->GetSize().X;
	float FloorPosMaxX = FloorPos.X + FloorCollider->GetSize().X;
	float PlayerPosMinY = PlayerPos.Y;
	float FloorPosMinY = FloorPos.Y;
	float PlayerPosMinX = PlayerPos.X;
	float FloorPosMinX = FloorPos.X;

	float PlayerVelocityX = PlayerRB->GetVelocity().X;
	float PlayerVelocityY = PlayerRB->GetVelocity().Y;

	float overlapX = min(PlayerPosMaxX, FloorPosMaxX) - max(PlayerPosMinX, FloorPosMinX);
	float overlapY = min(PlayerPosMaxY, FloorPosMaxY) - max(PlayerPosMinY, FloorPosMinY);

	if (overlapX < overlapY)
	{

		if (PlayerVelocityX > 0)
		{
			PlayerPos.X = FloorPosMinX - (PlayerPosMaxX - PlayerPosMinX);
		}
		else if (PlayerVelocityX < 0)
		{
			PlayerPos.X = FloorPosMaxX;
		}

		PlayerVelocityX = 0;
	}
	else
	{
		if (PlayerVelocityY > 0)
		{
			PlayerRB->SetIsGround(true);
			PlayerPos.Y = FloorPosMinY - (PlayerPosMaxY - PlayerPosMinY);
			WHUD::AddScore(1000);
			PlayerScript->WalkRight();
			return;
		}

		PlayerVelocityY = 0;
	}

	PlayerTr->SetPos(PlayerPos);
	PlayerRB->SetVelocity(sVector2<float>(PlayerVelocityX, PlayerVelocityY));
}

void Won::WFlagBlockScript::OnColliderStay(WCollider* Other)
{
}

void Won::WFlagBlockScript::OnColliderExit(WCollider* Other)
{
	WRigidbody* PlayerRB = Other->GetOwner()->GetComponent<WRigidbody>();
	PlayerRB->SetIsGround(false);
}
