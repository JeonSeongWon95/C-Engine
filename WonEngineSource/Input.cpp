#include "Input.h"
#include <iostream>
#include "WonApplication.h"

std::vector<Won::Input::aKey> Won::Input::Keys = {};
Won::mVector2<float> Won::Input::mMousePosition = {0.f, 0.f};

extern Won::WonApplication Engine;

namespace Won
{
	int ASCII[KeyType::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z',
		'X', 'C', 'V', 'B', 'N', 'M', VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON

	};
}



void Won::Input::Initialize()
{
	createKeys();
}

void Won::Input::Update()
{
	updateKey();
}

void Won::Input::createKeys()
{
	for (int i = 0; i < (int)KeyType::End; ++i)
	{
		aKey NewKey = {};
		NewKey.IsPressed = false;
		NewKey.State = KeyState::None;
		NewKey.Type = (KeyType)i;

		Keys.push_back(NewKey);
	}
}

void Won::Input::updateKey()
{
	for (Input::aKey& NewKey : Keys)
	{
		updatekey(NewKey);
	}
}

void Won::Input::updatekey(Input::aKey& NewKey)
{
	if (GetFocus())
	{
		if (isKeyDown(NewKey.Type))
		{
			updateKeyDown(NewKey);
		}
		else
		{
			updateKeyUp(NewKey);
		}
		SetMousePosition();
	}
	else
	{
		ClearKeys();
	}
}

bool Won::Input::isKeyDown(KeyType KeyName)
{
	return GetAsyncKeyState(ASCII[(int)KeyName]) & 0X8000;
}

void Won::Input::updateKeyDown(Input::aKey& NewKey)
{
	if (NewKey.IsPressed == true)
	{
		NewKey.State = KeyState::Pressed;
	}
	else
	{
		NewKey.State = KeyState::Down;
	}

	NewKey.IsPressed = true;
}

void Won::Input::updateKeyUp(Input::aKey& NewKey)
{
	if(NewKey.IsPressed == true)
	{
		NewKey.State = KeyState::Up;
	}
	else
	{
		NewKey.State = KeyState::None;
	}

	NewKey.IsPressed = false;
}

void Won::Input::ClearKeys()
{
	for (aKey& Key : Keys)
	{
		if (Key.State == KeyState::Down || Key.State == KeyState::Pressed)
		{
			Key.State = KeyState::Up;
		}
		else if (Key.State == KeyState::Up)
		{
			Key.State = KeyState::None;
		}

		Key.IsPressed = false;
	}
}

void Won::Input::SetMousePosition()
{
	POINT Cursorpos = {};
	GetCursorPos(&Cursorpos);
	ScreenToClient(Engine.GetEngineWND(), &Cursorpos);

	mMousePosition.X = static_cast<float>(Cursorpos.x);
	mMousePosition.Y = static_cast<float>(Cursorpos.y);
}
