#include "WInput.h"
#include <iostream>
#include "WonApplication.h"

std::vector<Won::WInput::aKey> Won::WInput::Keys = {};
Won::sVector2<float> Won::WInput::mMousePosition = { 0.f, 0.f };

extern Won::WonApplication Engine;

namespace Won
{
	int ASCII[KeyType::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'Z',
		'X', 'C', 'V', 'B', 'N', 'M', VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON, VK_RETURN

	};
}



void Won::WInput::Initialize()
{
	createKeys();
}

void Won::WInput::Update()
{
	updateKey();
}

void Won::WInput::createKeys()
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

void Won::WInput::updateKey()
{
	for (WInput::aKey& NewKey : Keys)
	{
		updatekey(NewKey);
	}
}

void Won::WInput::updatekey(WInput::aKey& NewKey)
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

bool Won::WInput::isKeyDown(KeyType KeyName)
{
	return GetAsyncKeyState(ASCII[(int)KeyName]) & 0X8000;
}

void Won::WInput::updateKeyDown(WInput::aKey& NewKey)
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

void Won::WInput::updateKeyUp(WInput::aKey& NewKey)
{
	if (NewKey.IsPressed == true)
	{
		NewKey.State = KeyState::Up;
	}
	else
	{
		NewKey.State = KeyState::None;
	}

	NewKey.IsPressed = false;
}

void Won::WInput::ClearKeys()
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

void Won::WInput::SetMousePosition()
{
	POINT mousePos = { };
	GetCursorPos(&mousePos);
	ScreenToClient(Engine.GetEngineWND(), &mousePos);

	UINT width = Engine.GetWidth();
	UINT height = Engine.GetHeight();

	mMousePosition.X = -1.0f;
	mMousePosition.Y = -1.0f;

	if (mousePos.x > 0 && mousePos.x < width)
		mMousePosition.X = mousePos.x;

	if (mousePos.y > 0 && mousePos.y < height)
		mMousePosition.Y = mousePos.y;

}
