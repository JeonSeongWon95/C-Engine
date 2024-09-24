#pragma once

namespace Won
{
	enum class eLayerType
	{
		None,
		BackGround,
		Tilemap,
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
		TileRender,
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