#pragma once

namespace Won
{
	enum class eLayerType
	{
		None,
		BackGround,
		Environment,
		Character,
		Player,
		Effect,
		Max = 16

	};

	enum class eComponentType
	{
		Transform,
		Collider,
		Script,
		Camera,
		SpriteRender,
		Animator,
		End
	};

	enum class eResourceType
	{
		Texture,
		Audio,
		Animation,
		None
	};

}