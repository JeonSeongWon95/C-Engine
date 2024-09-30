#include "WItemBlockScript.h"
#include "WCollider.h"
#include "WGameObject.h"
#include "WPlayerScript.h"
#include "WonObject.h"
#include "WHUD.h"
#include "WAnimator.h"
#include "WTime.h"
#include "Mushroom.h"
#include "WRigidbody.h"

Won::WItemBlockScript::WItemBlockScript()
	:mIsHit(false)
	, mStartposition(0)
	, mNoItem(false)
	, mItem(eItemType::None)
	, mResetHit(0)
	, mIsReset(false)
{
}

Won::WItemBlockScript::~WItemBlockScript()
{
}

void Won::WItemBlockScript::Initialize()
{
	int RandomItem = rand() % 3;

	switch (RandomItem)
	{
	case 0:
		mItem = eItemType::Mushroom;
		break;
	case 1:
		mItem = eItemType::Flower;
		break;
	case 2:
		mItem = eItemType::Star;
		break;
	default:
		break;
	}

	WTransform* Transform = GetOwner()->GetComponent<WTransform>();
	sVector2<float> Pos = Transform->GetPosition();

	mStartposition = Pos.Y;
}

void Won::WItemBlockScript::Update()
{
}

void Won::WItemBlockScript::LateUpdate()
{
	if (mNoItem)
	{
		WAnimator* Anim = GetOwner()->GetComponent<WAnimator>();
		Anim->PlayAnimation(L"Change", false);
	}
	else
	{
		WAnimator* Anim = GetOwner()->GetComponent<WAnimator>();
		Anim->PlayAnimation(L"Idle", false);
	}
}

void Won::WItemBlockScript::Render(HDC NewDC)
{

}

void Won::WItemBlockScript::OnColliderEnter(WCollider* Other)
{

	WTransform* PlayerTr = Other->GetOwner()->GetComponent<WTransform>();
	WRigidbody* PlayerRB = Other->GetOwner()->GetComponent<WRigidbody>();
	WPlayerScript* PlayerScript = Other->GetOwner()->GetComponent<WPlayerScript>();

	WTransform* BlockTransform = GetOwner()->GetComponent<WTransform>();
	WCollider* BlockCollider = GetOwner()->GetComponent<WCollider>();
	sVector2<float> PlayerPos = PlayerTr->GetPosition();
	sVector2<float> BlockPos = BlockTransform->GetPosition();

	if (PlayerScript == nullptr)
		return;


	float PlayerPosMaxY = PlayerPos.Y + Other->GetSize().Y;
	float BlockPosMaxY = BlockPos.Y + BlockCollider->GetSize().Y;
	float PlayerPosMaxX = PlayerPos.X + Other->GetSize().X;
	float BlockPosMaxX = BlockPos.X + BlockCollider->GetSize().X;
	float PlayerPosMinY = PlayerPos.Y;
	float BlockPosMinY = BlockPos.Y;
	float PlayerPosMinX = PlayerPos.X;
	float BlockPosMinX = BlockPos.X;

	float PlayerVelocityX = PlayerRB->GetVelocity().X;
	float PlayerVelocityY = PlayerRB->GetVelocity().Y;

	float overlapX = min(PlayerPosMaxX, BlockPosMaxX) - max(PlayerPosMinX, BlockPosMinX);
	float overlapY = min(PlayerPosMaxY, BlockPosMaxY) - max(PlayerPosMinY, BlockPosMinY);

	if (overlapX < overlapY)
	{

		if (PlayerVelocityX > 0)
		{
			PlayerPos.X = BlockPosMinX - (PlayerPosMaxX - PlayerPosMinX);
		}
		else if (PlayerVelocityX < 0)
		{
			PlayerPos.X = BlockPosMaxX;
		}

		PlayerVelocityX = 0;
	}
	else
	{
		if (PlayerVelocityY > 0)
		{
			PlayerRB->SetIsGround(true);
			PlayerPos.Y = BlockPosMinY - (PlayerPosMaxY - PlayerPosMinY);
		}
		else if (PlayerVelocityY < 0)
		{
			PlayerPos.Y = BlockPosMaxY;

			if (!mNoItem)
			{
				WHUD::AddScore(100);
				Mushroom* Mush = InstanceSpawn<Mushroom>(eLayerType::Character
					, sVector2<float>(BlockPos.X, BlockPos.Y - 50.0f));
				mNoItem = true;
			}
			
		}

		PlayerVelocityY = 0;
	}

	PlayerTr->SetPos(PlayerPos);
	PlayerRB->SetVelocity(sVector2<float>(PlayerVelocityX, PlayerVelocityY));

}

void Won::WItemBlockScript::OnColliderStay(WCollider* Other)
{
}

void Won::WItemBlockScript::OnColliderExit(WCollider* Other)
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
