#include "Input.h"

namespace thomas
{
	DirectX::GamePad Input::s_gamePad;
	DirectX::Keyboard Input::s_keyboard;
	DirectX::Mouse Input::s_mouse;


	bool Input::IsKeyDown(DirectX::Keyboard::Keys key)
	{
		return s_keyboard.GetState().IsKeyDown((DirectX::Keyboard::Keys));
	}

	bool Input::IsButtonDown(Buttons button)
	{
		switch (button)
		{
		case Buttons::A:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsAPressed();
		}
		case Buttons::B:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsBPressed();
		}
		case Buttons::X:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsXPressed();
		}
		case Buttons::Y:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsYPressed();
		}
		case Buttons::DPAD_UP:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsDPadUpPressed();
		}
		case Buttons::DPAD_DOWN:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsDPadDownPressed();
		}
		case Buttons::DPAD_LEFT:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsDPadLeftPressed();
		}
		case Buttons::DPAD_RIGHT:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsDPadRightPressed();
		}
		case Buttons::LS:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsLeftStickPressed();
		}
		case Buttons::RS:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsRightStickPressed();
		}
		case Buttons::LB:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsLeftShoulderPressed();
		}
		case Buttons::RB:
		{
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsRightShoulderPressed();
		}
		}
		return false;
	}

	bool Input::Init()
	{
	}

	LONG Input::GetMouseY()
	{
		return s_mouse.GetState().y;
	}

	LONG Input::GetMouseX()
	{
		return s_mouse.GetState().x;
	}

	Input::Input()
	{
	}

	Input::~Input()
	{
	}
}