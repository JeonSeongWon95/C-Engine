#include "WAnimation.h"

Won::WAnimation::WAnimation()
	: WResource(eResourceType::Animation)
	, MainTexture(nullptr)
	, Sprites{}
	, mIndex(-1)
	, bIsCompleted(false)
{

}

Won::WAnimation::~WAnimation()
{
}
