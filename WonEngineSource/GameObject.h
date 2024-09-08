#pragma once
#include "includeHeader.h"
#include "Component.h"

namespace Won
{
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC NewDC);

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



	};
}

