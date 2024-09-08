#include "GameObject.h"
#include "Transform.h"

Won::GameObject::GameObject()
{
	Components.resize((int)ComponentType::End);
	AddTransform();
}

Won::GameObject::~GameObject()
{
	for (Component* NewComponent : Components)
	{
		delete NewComponent;
		NewComponent = nullptr;
	}
}
void Won::GameObject::Initialize()
{
	for (auto NewComponent : Components)
	{
		if (NewComponent == nullptr)
			continue;

		NewComponent->Initialize();
	}

}

void Won::GameObject::Update()
{
	for (auto NewComponent : Components)
	{
		if (NewComponent == nullptr)
			continue;

		NewComponent->Update();
	}

}
void Won::GameObject::LateUpdate()
{
	for (auto NewComponent : Components)
	{
		if (NewComponent == nullptr)
			continue;

		NewComponent->LateUpdate();
	}
}
void Won::GameObject::Render(HDC NewDC)
{
	for(auto NewComponent : Components)
	{
		if (NewComponent == nullptr)
			continue;

		NewComponent->Render(NewDC);
	}

}

void Won::GameObject::AddTransform()
{
	AddComponent<Transform>();
}
