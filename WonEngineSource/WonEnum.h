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
		Max = 16

	};

	enum class eComponentType
	{
		Transform,
		SpriteRender,
		Script,
		Camera,
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