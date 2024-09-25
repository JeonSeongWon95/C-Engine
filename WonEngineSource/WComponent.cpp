#include "WComponent.h"

Won::WComponent::WComponent(eComponentType NewType)
	: Owner(nullptr)
	, aType(NewType)
{

}

Won::WComponent::~WComponent()
{
	if(Owner)
	{
		Owner = nullptr;
	}
}

void Won::WComponent::Initialize()
{
}

void Won::WComponent::Update()
{
}

void Won::WComponent::LateUpdate()
{
}

void Won::WComponent::Render(HDC NewDC)
{
}
