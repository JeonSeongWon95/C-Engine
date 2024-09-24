#include "Component.h"

Won::Component::Component(eComponentType NewType)
	: Owner(nullptr)
	, aType(NewType)
{

}

Won::Component::~Component()
{
	if(Owner)
	{
		Owner = nullptr;
	}
}

void Won::Component::Initialize()
{
}

void Won::Component::Update()
{
}

void Won::Component::LateUpdate()
{
}

void Won::Component::Render(HDC NewDC)
{
}
