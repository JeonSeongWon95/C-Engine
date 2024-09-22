#pragma once
#include "includeHeader.h"
#include "Component.h"

namespace Won
{
	class GameObject
	{
	public:
		enum class eState
		{
			Active,
			Pased,
			Death,
			End
		};

		GameObject();
		virtual ~GameObject();

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
				for (Component* OneComponent : Components)
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
		std::vector<Component*> Components;
		eState ObjectState;

	};
}

