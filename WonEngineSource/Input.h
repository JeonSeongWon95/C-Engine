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
		LBUTTON, RBUTTON,
		End

	};
	class Input
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
		
		static bool GetKeyDown(KeyType Key) { return Keys[(unsigned int)Key].State == KeyState::Down; }
		static bool GetKeyUp(KeyType Key) { return Keys[(unsigned int)Key].State == KeyState::Up; }
		static bool GetKey(KeyType Key) { return Keys[(unsigned int)Key].State == KeyState::Pressed; }
		static mVector2<float> GetMousePosition() { return mMousePosition; }


	private:
		static void createKeys();
		static void updateKey();
		static void updatekey(Input::aKey& NewKey);
		static bool isKeyDown(KeyType KeyName);
		static void updateKeyDown(Input::aKey& NewKey);
		static void updateKeyUp(Input::aKey& NewKey);
		static void ClearKeys();
		static void SetMousePosition();


		static std::vector<aKey> Keys;
		static mVector2<float> mMousePosition;
	};
}
