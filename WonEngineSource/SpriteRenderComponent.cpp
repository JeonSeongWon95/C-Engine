#include "SpriteRenderComponent.h"
#include "GameObject.h"
#include "Transform.h"

Won::SpriteRenderComponent::SpriteRenderComponent()
	:aImage(nullptr)
	, Width(0)
	, Height(0)
{
}

Won::SpriteRenderComponent::~SpriteRenderComponent()
{
}

void Won::SpriteRenderComponent::Initialize()
{
}

void Won::SpriteRenderComponent::Update()
{
}

void Won::SpriteRenderComponent::LateUpdate()
{
}

void Won::SpriteRenderComponent::Render(HDC NewDC)
{
	FVector2* vc = GetOwner()->GetComponent<Transform>()->GetComponentPosition();

	Gdiplus::Graphics graphics(NewDC);
	graphics.DrawImage(aImage, Gdiplus::Rect(static_cast<INT>(vc->X), static_cast<INT>(vc->Y), Width, Height));

}

void Won::SpriteRenderComponent::ImageLoad(const std::wstring& Path)
{
	aImage = Gdiplus::Image::FromFile(Path.c_str());
	Width = aImage->GetWidth();
	Height = aImage->GetHeight();
}
