#include "Component.h"

Won::Component::Component(ComponentType NewType)
	: Owner(nullptr)
	, aType(NewType)
{
}

Won::Component::~Component()
{
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
