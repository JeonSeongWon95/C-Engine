#include "GameObject.h"
#include "Transform.h"

Won::GameObject::GameObject()
{
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
		NewComponent->Initialize();
	}

}

void Won::GameObject::Update()
{
	for (auto NewComponent : Components)
	{
		NewComponent->Update();
	}

}
void Won::GameObject::LateUpdate()
{
	for (auto NewComponent : Components)
	{
		NewComponent->LateUpdate();
	}
}
void Won::GameObject::Render(HDC NewDC)
{
	for(auto NewComponent : Components)
	{
		NewComponent->Render(NewDC);
	}

}

void Won::GameObject::AddTransform()
{
	AddComponent<Transform>();
}
