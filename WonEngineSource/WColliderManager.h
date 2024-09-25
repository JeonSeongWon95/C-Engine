#pragma once
#include "includeHeader.h"


namespace Won
{
	class WColliderManager
	{
	public:
		union ColliderID
		{
			struct 
			{
				UINT32 LEFT;
				UINT32 RIGHT;
			};

			UINT64 ID;
		};

		WColliderManager();
		~WColliderManager();

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC NewDC);

		static void SetColliderEnable(eLayerType Left, eLayerType Right, bool IsEnable);
		static void CollisionCheckLayer(class WScene* Scene, eLayerType Left, eLayerType Right);
		static void CollisionCheckCollider(class WCollider* Left, WCollider* Right);
		static bool Intersect(WCollider* Left, WCollider* Right);
		static void Clear();

	private:
		static std::bitset<(UINT)eLayerType::Max> ColliderMatrix[(UINT)eLayerType::Max];
		static std::unordered_map<UINT64, bool> mCollisionMap;
	};
}

