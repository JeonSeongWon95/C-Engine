#include "WColliderManager.h"
#include "WSceneManager.h"
#include "WGameObject.h"
#include "WLayer.h"
#include "WCollider.h"
#include "WTransform.h"

std::bitset<(UINT)Won::eLayerType::Max> Won::WColliderManager::ColliderMatrix[(UINT)Won::eLayerType::Max] = {};
std::unordered_map<UINT64, bool> Won::WColliderManager::mCollisionMap = {};

Won::WColliderManager::WColliderManager()
{

}

Won::WColliderManager::~WColliderManager()
{
}

void Won::WColliderManager::Initialize()
{
}

void Won::WColliderManager::Update()
{
	WScene* mScene = WSceneManager::GetActiveScene();

	for(UINT Row = 0; Row < (UINT)eLayerType::Max; ++Row)
	{
		for(UINT Col = 0; Col < (UINT)eLayerType::Max; ++Col)
		{
			if (ColliderMatrix[Row][Col] == true)
			{
				CollisionCheckLayer(mScene, (eLayerType)Row, (eLayerType)Col);
			}
		}
	}
}

void Won::WColliderManager::LateUpdate()
{
}

void Won::WColliderManager::Render(HDC NewDC)
{
}

void Won::WColliderManager::SetColliderEnable(eLayerType Left, eLayerType Right, bool IsEnable)
{
	UINT Row = 0;
	UINT Col = 0;

	if(Left >= Right)
	{
		Row = (UINT)Left;
		Col = (UINT)Right;
	}
	else
	{
		Row = (UINT)Right;
		Col = (UINT)Left;
	}

	ColliderMatrix[Row][Col] = IsEnable;
}

void Won::WColliderManager::CollisionCheckLayer(WScene* Scene, eLayerType Left, eLayerType Right)
{
	std::vector<class WGameObject*> Lefts = WSceneManager::GetGameObjects(Left);
	std::vector<class WGameObject*> Rights = WSceneManager::GetGameObjects(Right);

	for(WGameObject* Left : Lefts)
	{
		if (Left->IsActive() == false)
			continue;

		WCollider* LeftCollider = Left->GetComponent<WCollider>();

		if (LeftCollider == nullptr)
			continue;

		for(WGameObject* Right : Rights)
		{
			if (Left == Right)
				continue;
			if (Right->IsActive() == false)
				continue;

			WCollider* RightCollider = Right->GetComponent<WCollider>();

			if (RightCollider == nullptr)
				continue;

			CollisionCheckCollider(LeftCollider, RightCollider);

		}
	}
}

void Won::WColliderManager::CollisionCheckCollider(WCollider* Left, WCollider* Right)
{
	UINT32 LeftID = Left->GetID();
	UINT32 RightID = Right->GetID();

	ColliderID CD = {};
	CD.LEFT = LeftID;
	CD.RIGHT = RightID;

	std::unordered_map<UINT64, bool>::iterator Iter = mCollisionMap.find(CD.ID);

	if(Iter == mCollisionMap.end())
	{
		mCollisionMap.insert(std::make_pair(CD.ID, false));
		Iter = mCollisionMap.find(CD.ID);
	}

	if(Intersect(Left, Right))
	{
		if(Iter->second == false)
		{
			Left->OnColliderEnter(Right);
			Right->OnColliderEnter(Left);
			Iter->second = true;
		}
		else
		{
			Left->OnColliderStay(Right);
			Right->OnColliderStay(Left);
		}
	}
	else
	{
		if (Iter->second == true)
		{
			Left->OnColliderExit(Right);
			Right->OnColliderExit(Left);
			Iter->second = false;
		}
	}

}

bool Won::WColliderManager::Intersect(WCollider* Left, WCollider* Right)
{

	WTransform* LeftTransform = Left->GetOwner()->GetComponent<WTransform>();
	WTransform* RightTransform = Right->GetOwner()->GetComponent<WTransform>();

	sVector2<float> LeftPos = LeftTransform->GetPosition();
	sVector2<float> RightPos = RightTransform->GetPosition();

	sVector2<float> LeftSize = Left->GetSize();
	sVector2<float> RightSize = Right->GetSize();

	
	if (Left->GetColliderType() == WCollider::eColliderType::Box && Right->GetColliderType() == WCollider::eColliderType::Box)
	{

		//if (LeftPos.X <= RightPos.X + RightSize.X && )
		//{
		//	return true;
		//}
	}
	else if(Left->GetColliderType() == WCollider::eColliderType::Sphere && Right->GetColliderType() == WCollider::eColliderType::Sphere)
	{

		if(fabs(LeftSize.X / 2 + RightSize.X/ 2) >= fabs(((LeftPos - (LeftSize / 2)) - (RightPos - (RightSize / 2))).Lenth()))
		{
			return true;
		}
	}
	else if(Left->GetColliderType() == WCollider::eColliderType::Sphere && Right->GetColliderType() == WCollider::eColliderType::Box ||
		Left->GetColliderType() == WCollider::eColliderType::Box && Right->GetColliderType() == WCollider::eColliderType::Sphere)
	{

	}

	return false;
}

void Won::WColliderManager::Clear()
{
	ColliderMatrix->reset();
	mCollisionMap.clear();
}
