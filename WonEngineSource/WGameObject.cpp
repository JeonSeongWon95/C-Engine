#include "WGameObject.h"
#include "WTransform.h"

Won::WGameObject::WGameObject()
	:ObjectState(eState::Active)
{
	Components.resize((int)eComponentType::End);
	AddTransform();
}

Won::WGameObject::~WGameObject()
{
	for (WComponent* NewComponent : Components)
	{
		delete NewComponent;
		NewComponent = nullptr;
	}

	Components.clear();
}
void Won::WGameObject::Initialize()
{
	for (auto NewComponent : Components)
	{
		if (NewComponent == nullptr)
			continue;

		NewComponent->Initialize();
	}

}

void Won::WGameObject::Update()
{
	for (auto NewComponent : Components)
	{
		if (NewComponent == nullptr)
			continue;

		NewComponent->Update();
	}

}
void Won::WGameObject::LateUpdate()
{
	for (auto NewComponent : Components)
	{
		if (NewComponent == nullptr)
			continue;

		NewComponent->LateUpdate();
	}
}
void Won::WGameObject::Render(HDC NewDC)
{
	for(auto NewComponent : Components)
	{
		if (NewComponent == nullptr)
			continue;

		NewComponent->Render(NewDC);
	}

}

void Won::WGameObject::AddTransform()
{
	WTransform* Tr = AddComponent<WTransform>();
	Tr->SetName(L"WTransform");
}
