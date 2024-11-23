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
	Vector2 Pos = Transform->GetPosition();

	mStartposition = Pos.y;
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
	Vector2 PlayerPos = PlayerTr->GetPosition();
	Vector2 BlockPos = BlockTransform->GetPosition();

	if (PlayerScript == nullptr)
		return;


	float PlayerPosMaxY = PlayerPos.y + Other->GetSize().y;
	float BlockPosMaxY = BlockPos.y + BlockCollider->GetSize().y;
	float PlayerPosMaxX = PlayerPos.x + Other->GetSize().x;
	float BlockPosMaxX = BlockPos.x + BlockCollider->GetSize().x;
	float PlayerPosMinY = PlayerPos.y;
	float BlockPosMinY = BlockPos.y;
	float PlayerPosMinX = PlayerPos.x;
	float BlockPosMinX = BlockPos.x;

	float PlayerVelocityX = PlayerRB->GetVelocity().x;
	float PlayerVelocityY = PlayerRB->GetVelocity().y;

	float overlapX = min(PlayerPosMaxX, BlockPosMaxX) - max(PlayerPosMinX, BlockPosMinX);
	float overlapY = min(PlayerPosMaxY, BlockPosMaxY) - max(PlayerPosMinY, BlockPosMinY);

	if (overlapX < overlapY)
	{

		if (PlayerVelocityX > 0)
		{
			PlayerPos.x = BlockPosMinX - (PlayerPosMaxX - PlayerPosMinX);
		}
		else if (PlayerVelocityX < 0)
		{
			PlayerPos.x = BlockPosMaxX;
		}

		PlayerVelocityX = 0;
	}
	else
	{
		if (PlayerVelocityY > 0)
		{
			PlayerRB->SetIsGround(true);
			PlayerPos.y = BlockPosMinY - (PlayerPosMaxY - PlayerPosMinY);
		}
		else if (PlayerVelocityY < 0)
		{
			PlayerPos.y = BlockPosMaxY;

			if (!mNoItem)
			{
				WHUD::AddScore(100);
				Mushroom* Mush = InstanceSpawn<Mushroom>(eLayerType::Character
					, Vector2(BlockPos.x, BlockPos.y - 50.0f));
				mNoItem = true;
			}
			
		}

		PlayerVelocityY = 0;
	}

	PlayerTr->SetPos(PlayerPos);
	PlayerRB->SetVelocity(Vector2(PlayerVelocityX, PlayerVelocityY));

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

	if (PlayerTr->GetPosition().y < FloorTr->GetPosition().y)
	{
		PlayerRB->SetIsGround(false);
	}
}
