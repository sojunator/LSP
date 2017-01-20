#include "Input.h"

namespace thomas
{
	DirectX::GamePad Input::s_gamePad;
	DirectX::Keyboard Input::s_keyboard;
	DirectX::Mouse Input::s_mouse;


	bool Input::IsKeyDown(DirectX::Keyboard::Keys key)
	{
		return s_keyboard.GetState().IsKeyDown(key);
	}

	bool Input::IsButtonDown(Buttons button)
	{
		switch (button)
		{
		case Buttons::A:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsAPressed();
		case Buttons::B:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsBPressed();
		case Buttons::X:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsXPressed();
		case Buttons::Y:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsYPressed();
		case Buttons::DPAD_UP:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsDPadUpPressed();
		case Buttons::DPAD_DOWN:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsDPadDownPressed();
		case Buttons::DPAD_LEFT:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsDPadLeftPressed();
		case Buttons::DPAD_RIGHT:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsDPadRightPressed();
		case Buttons::LS:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsLeftStickPressed();
		case Buttons::RS:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsRightStickPressed();
		case Buttons::LB:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsLeftShoulderPressed();
		case Buttons::RB:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsRightShoulderPressed();
		case Buttons::LT:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsLeftTriggerPressed();
		case Buttons::RT:
			return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).IsRightTriggerPressed();
		}
		return false;
	}

	float Input::GetLeftStickY()
	{
		return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).thumbSticks.leftY;
	}

	float Input::GetLeftStickX()
	{
		return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).thumbSticks.leftX;
	}

	float Input::GetRightStickY()
	{
		return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).thumbSticks.rightY;
	}

	float Input::GetRightStickX()
	{
		return s_gamePad.GetState(0, DirectX::GamePad::DEAD_ZONE_INDEPENDENT_AXES).thumbSticks.rightX;
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

	bool Input::IsMouseButtonDown(MouseButtons button)
	{
		switch (button)
		{
		case LEFT:
			return s_mouse.GetState().leftButton % 2;
		case RIGHT:
			return s_mouse.GetState().rightButton % 2;
		case SCROLL:
			return s_mouse.GetState().middleButton % 2;
		}
		return false;
	}

	Input::Input()
	{
	}

	Input::~Input()
	{
	}
}