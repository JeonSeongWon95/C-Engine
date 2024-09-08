#pragma once

namespace Won
{
	enum class LayerType
	{
		None,
		BackGround,
		Environment,
		Character,
		Player,
		Max = 16

	};

	enum class ComponentType
	{
		Transform,
		SpriteRender,
		Script,
		Camera,
		End
	};

	enum class ResourceType
	{
		Texture,
		Audio,
		None
	};

}