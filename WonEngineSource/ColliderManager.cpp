#include "ColliderManager.h"
#include "Scene_LevelManager.h"
#include "GameObject.h"
#include "WLayer.h"
#include "Collider.h"
#include "Transform.h"

std::bitset<(UINT)Won::eLayerType::Max> Won::ColliderManager::ColliderMatrix[(UINT)Won::eLayerType::Max] = {};
std::unordered_map<UINT64, bool> Won::ColliderManager::mCollisionMap = {};

Won::ColliderManager::ColliderManager()
{

}

Won::ColliderManager::~ColliderManager()
{
}

void Won::ColliderManager::Initialize()
{
}

void Won::ColliderManager::Update()
{
	Scene_Level* mScene = Scene_LevelManager::GetActiveScene();

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

void Won::ColliderManager::LateUpdate()
{
}

void Won::ColliderManager::Render(HDC NewDC)
{
}

void Won::ColliderManager::SetColliderEnable(eLayerType Left, eLayerType Right, bool IsEnable)
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

void Won::ColliderManager::CollisionCheckLayer(Scene_Level* Scene, eLayerType Left, eLayerType Right)
{
	std::vector<class GameObject*> Lefts = Scene_LevelManager::GetActiveScene()->GetLayer(Left)->GetGameObject();
	std::vector<class GameObject*> Rights = Scene_LevelManager::GetActiveScene()->GetLayer(Right)->GetGameObject();

	for(GameObject* Left : Lefts)
	{
		if (Left->IsActive() == false)
			continue;

		Collider* LeftCollider = Left->GetComponent<Collider>();

		if (LeftCollider == nullptr)
			continue;

		for(GameObject* Right : Rights)
		{
			if (Left == Right)
				continue;
			if (Right->IsActive() == false)
				continue;

			Collider* RightCollider = Right->GetComponent<Collider>();

			if (RightCollider == nullptr)
				continue;

			CollisionCheckCollider(LeftCollider, RightCollider);

		}
	}
}

void Won::ColliderManager::CollisionCheckCollider(Collider* Left, Collider* Right)
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

bool Won::ColliderManager::Intersect(Collider* Left, Collider* Right)
{

	Transform* LeftTransform = Left->GetOwner()->GetComponent<Transform>();
	Transform* RightTransform = Right->GetOwner()->GetComponent<Transform>();

	mVector2<float> LeftPos = Left->GetOffset() + LeftTransform->GetPosition();
	mVector2<float> RightPos = Right->GetOffset() + RightTransform->GetPosition();

	mVector2<float> LeftSize = Left->GetSize();
	mVector2<float> RightSize = Right->GetSize();


	if(fabs(LeftPos.X - RightPos.X) < fabs(LeftSize.X / 2.0f + RightSize.X / 2.0f) && 
		fabs(LeftPos.Y - RightPos.Y) < fabs(LeftSize.Y / 2.0f + RightSize.Y / 2.0f))
	{
		return true;
	}

	return false;
}
