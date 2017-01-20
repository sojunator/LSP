#pragma once
#include <Windows.h>
#include <string>
#include "Common.h"
#include "utils\GamePad.h"
#include "utils\Keyboard.h"
#include "utils\Mouse.h"

namespace thomas
{
	class Input
	{
	public:


		static enum Buttons
		{
			//Main Buttons
			A,
			B,
			X,
			Y,
			//DPAD
			DPAD_UP,
			DPAD_DOWN,
			DPAD_LEFT,
			DPAD_RIGHT,
			//STICKS (click)
			LS,
			RS,
			//BUMPERS
			LB,
			RB
		};

		static bool Init();

		static LONG GetMouseY();
		static LONG GetMouseX();
		static bool IsKeyDown(DirectX::Keyboard::Keys vKey);
		static bool IsButtonDown(Buttons button);

		Input();
		~Input();

		

	private:
		static DirectX::Mouse s_mouse;
		static DirectX::Keyboard s_keyboard;
		static DirectX::GamePad s_gamePad;
	};
}