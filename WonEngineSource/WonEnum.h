#pragma once

namespace Won
{
	enum class eLayerType
	{
		None,
		BackGround,
		Tilemap,
		Environment,
		Item,
		Character,
		Player,
		Floor,
		Effect,
		Max = 16

	};

	enum class eComponentType
	{
		WTransform,
		AudioListener,
		AudioSource,
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
		None,
		HUD,
		Button,
		End
	};

	enum class eDirection
	{
		None,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		END
	};

	enum class eItemType
	{
		None,
		Mushroom,
		Flower,
		Star,
		End
	};

}