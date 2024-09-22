#pragma once
#include "includeHeader.h"


namespace Won
{
	class ColliderManager
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

		ColliderManager();
		~ColliderManager();

		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC NewDC);

		static void SetColliderEnable(eLayerType Left, eLayerType Right, bool IsEnable);
		static void CollisionCheckLayer(class Scene_Level* Scene, eLayerType Left, eLayerType Right);
		static void CollisionCheckCollider(class Collider* Left, Collider* Right);
		static bool Intersect(Collider* Left, Collider* Right);

	private:
		static std::bitset<(UINT)eLayerType::Max> ColliderMatrix[(UINT)eLayerType::Max];
		static std::unordered_map<UINT64, bool> mCollisionMap;
	};
}

