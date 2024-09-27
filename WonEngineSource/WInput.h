#pragma once
#include "includeHeader.h"

namespace Won
{
	enum KeyState
	{
		 None
		,Down
		,Pressed
		,Up
	};
	enum KeyType
	{
		Q, W, E, R, T, Y, U, I, O, P, 
		A, S, D, F, G, H, J, K, L, Z, 
		X, C, V, B, N, M, LEFT, RIGHT, UP, DOWN,
		LBUTTON, RBUTTON, ENTER,
		End

	};
	class WInput
	{
		struct aKey
		{
			KeyState State;
			KeyType Type;
			bool IsPressed;
		};
	public:

		static void Initialize();
		static void Update();
		
		__forceinline static bool GetKeyDown(KeyType Key) { return Keys[(unsigned int)Key].State == KeyState::Down; }
		__forceinline static bool GetKeyUp(KeyType Key) { return Keys[(unsigned int)Key].State == KeyState::Up; }
		__forceinline static bool GetKey(KeyType Key) { return Keys[(unsigned int)Key].State == KeyState::Pressed; }
		static sVector2<float> GetMousePosition() { return mMousePosition; }


	private:
		static void createKeys();
		static void updateKey();
		static void updatekey(WInput::aKey& NewKey);
		static bool isKeyDown(KeyType KeyName);
		static void updateKeyDown(WInput::aKey& NewKey);
		static void updateKeyUp(WInput::aKey& NewKey);
		static void ClearKeys();
		static void SetMousePosition();


		static std::vector<aKey> Keys;
		static sVector2<float> mMousePosition;
	};
}
