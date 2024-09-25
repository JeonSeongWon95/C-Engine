#pragma once
#include "includeHeader.h"
#include "WComponent.h"

namespace Won
{
	class WGameObject
	{
	public:
		enum class eState
		{
			Active,
			Pased,
			Death,
			End
		};

		WGameObject();
		virtual ~WGameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC NewDC);
		virtual void SetActive(bool NewActive)
		{
			if (NewActive) { ObjectState = eState::Active; }
			if (!NewActive) { ObjectState = eState::Pased; }
		}
		virtual void DoDeath()
		{
			ObjectState = eState::Death;
		}
		virtual bool IsActive() { return ObjectState == eState::Active; }
		virtual eState& GetActive() { return ObjectState; }

		eLayerType GetLayerType() { return mLayerType; }
		void SetLayerType(eLayerType NewLayer) { mLayerType = NewLayer; }

		template<typename T>
		T* AddComponent()
		{
			T* NewComponent = new T;
			NewComponent->SetOwner(this);
			NewComponent->Initialize();

			Components[(int)(NewComponent->GetType())] = NewComponent;
			return NewComponent;
		}

		template<typename T>
		T* GetComponent()
		{
			T* findComponent = nullptr;

			if (Components.size() > 0)
			{
				for (WComponent* OneComponent : Components)
				{
					findComponent = dynamic_cast<T*>(OneComponent);

					if (findComponent != nullptr)
					{
						break;
					}
				}
			}
			return findComponent;
		};

	protected:
		void AddTransform();
		std::vector<WComponent*> Components;
		eState ObjectState;
		eLayerType mLayerType;

	};
}

