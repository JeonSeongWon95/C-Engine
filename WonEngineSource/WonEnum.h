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
		Floor,
		Effect,
		Max = 16

	};

	enum class eComponentType
	{
		WTransform,
		WCollider,
		Rigidbody,
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

	enum class eUIType
	{
		End
	};

}