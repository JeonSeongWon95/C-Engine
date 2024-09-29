#include "WBlockScript.h"
#include "WCollider.h"
#include "WGameObject.h"
#include "WPlayerScript.h"
#include "WonObject.h"
#include "WTransform.h"
#include "WTime.h"
#include "WHUD.h"
#include "WRigidbody.h"

Won::WBlockScript::WBlockScript()
	:mIsHit(false)
	, mStartposition(0)
{
}

Won::WBlockScript::~WBlockScript()
{
}

void Won::WBlockScript::Initialize()
{
	WTransform* Transform = GetOwner()->GetComponent<WTransform>();
	sVector2<float> Pos = Transform->GetPosition();

	mStartposition = Pos.Y;
}

void Won::WBlockScript::Update()
{
	if (mIsHit)
	{
		WTransform* Transform = GetOwner()->GetComponent<WTransform>();
		sVector2<float> Pos = Transform->GetPosition();

		if (Pos.Y >= mStartposition - 30.0f)
		{
			Pos.Y -= (100.0f * WTime::GetDeltaSeconds());
			Transform->SetPos(Pos);
		}
		else
		{
			mIsHit = false;
		}
	}
	else
	{
		WTransform* Transform = GetOwner()->GetComponent<WTransform>();
		sVector2<float> Pos = Transform->GetPosition();

		if (Pos.Y <= mStartposition)
		{
			Pos.Y += (100.0f * WTime::GetDeltaSeconds());
			Transform->SetPos(Pos);
		}
	}
}

void Won::WBlockScript::LateUpdate()
{
}

void Won::WBlockScript::Render(HDC NewDC)
{
}

void Won::WBlockScript::OnColliderEnter(WCollider* Other)
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
		}
		else if (PlayerVelocityY < 0)
		{
			PlayerPos.Y = FloorPosMaxY;

			if (PlayerScript->GetPlayerSize() == WPlayerScript::ePlayerSize::Small)
			{
				mIsHit = true;
			}
			else
			{
				WHUD::AddScore(100);
				Destroy(GetOwner());
			}
		}
		PlayerVelocityY = 0;
	}

	PlayerTr->SetPos(PlayerPos);
	PlayerRB->SetVelocity(sVector2<float>(PlayerVelocityX, PlayerVelocityY));
}

void Won::WBlockScript::OnColliderStay(WCollider* Other)
{
}

void Won::WBlockScript::OnColliderExit(WCollider* Other)
{
	WTransform* PlayerTr = Other->GetOwner()->GetComponent<WTransform>();
	WTransform* FloorTr = GetOwner()->GetComponent<WTransform>();
	WRigidbody* PlayerRB = Other->GetOwner()->GetComponent<WRigidbody>();

	if (PlayerTr == nullptr || PlayerRB == nullptr)
		return;

	if (PlayerTr->GetPosition().Y < FloorTr->GetPosition().Y)
	{
		PlayerRB->SetIsGround(false);
	}
}
