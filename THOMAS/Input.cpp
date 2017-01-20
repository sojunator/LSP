#include "Input.h"
#include "Window.h"

namespace thomas
{
	std::unique_ptr<DirectX::Keyboard> Input::s_keyboard;
	std::unique_ptr<DirectX::Mouse> Input::s_mouse;
	std::unique_ptr<DirectX::GamePad> Input::s_gamePad;

	DirectX::Mouse::State Input::s_mouseState;
	DirectX::Keyboard::State Input::s_keyboardState;
	DirectX::GamePad::State Input::s_gamePadState;

	bool Input::s_initialized;

	bool Input::IsKeyDown(Keys key)
	{
		return s_keyboardState.IsKeyDown((DirectX::Keyboard::Keys)key);
	}

	bool Input::IsButtonDown(Buttons button)
	{
		if (!s_gamePadState.IsConnected()) //Always false if no gamePad.
			return false;
		switch (button)
		{
		case Buttons::A:
			return s_gamePadState.IsAPressed();
		case Buttons::B:
			return s_gamePadState.IsBPressed();
		case Buttons::X:
			return s_gamePadState.IsXPressed();
		case Buttons::Y:
			return s_gamePadState.IsYPressed();
		case Buttons::DPAD_UP:
			return s_gamePadState.IsDPadUpPressed();
		case Buttons::DPAD_DOWN:
			return s_gamePadState.IsDPadDownPressed();
		case Buttons::DPAD_LEFT:
			return s_gamePadState.IsDPadLeftPressed();
		case Buttons::DPAD_RIGHT:
			return s_gamePadState.IsDPadRightPressed();
		case Buttons::LS:
			return s_gamePadState.IsLeftStickPressed();
		case Buttons::RS:
			return s_gamePadState.IsRightStickPressed();
		case Buttons::LB:
			return s_gamePadState.IsLeftShoulderPressed();
		case Buttons::RB:
			return s_gamePadState.IsRightShoulderPressed();
		case Buttons::LT:
			return s_gamePadState.IsLeftTriggerPressed();
		case Buttons::RT:
			return s_gamePadState.IsRightTriggerPressed();
		}
		return false;
	}

	float Input::GetLeftStickY()
	{
		return s_gamePadState.thumbSticks.leftY;
	}

	float Input::GetLeftStickX()
	{
		return s_gamePadState.thumbSticks.leftX;
	}

	float Input::GetRightStickY()
	{
		return s_gamePadState.thumbSticks.rightY;
	}

	float Input::GetRightStickX()
	{
		return s_gamePadState.thumbSticks.rightX;
	}

	bool Input::Init()
	{
		s_keyboard = std::make_unique<DirectX::Keyboard>();
		s_mouse = std::make_unique<DirectX::Mouse>();
		s_gamePad = std::make_unique<DirectX::GamePad>();

		s_mouse->SetWindow(Window::GetWindowHandler());
		s_initialized = Window::Initialized();
		return s_initialized;
	}

	void Input::Update()
	{
		if (s_initialized) 
		{
			s_keyboardState = s_keyboard->GetState();
			s_gamePadState = s_gamePad->GetState(0);
			s_mouseState = s_mouse->GetState();
		}
		
	}

	void Input::ProcessKeyboard(UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (s_initialized)
			s_keyboard->ProcessMessage(message, wParam, lParam);
	}

	void Input::ProcessMouse(UINT message, WPARAM wParam, LPARAM lParam)
	{
		if(s_initialized)
			s_mouse->ProcessMessage(message, wParam, lParam);
	}

	void Input::ProcessGamePad(UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (s_initialized)
		{
			switch (message)
			{

			case WM_SETFOCUS:
				s_gamePad->Resume();
			case WM_KILLFOCUS:
				s_gamePad->Suspend();
				break;
			}
		}
		
	}

	LONG Input::GetMouseY()
	{
		return s_mouseState.y;
	}

	LONG Input::GetMouseX()
	{
		return s_mouseState.x;
	}

	bool Input::IsMouseButtonDown(MouseButtons button)
	{
		switch (button)
		{
		case MouseButtons::LEFT:
			return s_mouseState.leftButton % 2;
		case MouseButtons::RIGHT:
			return s_mouseState.rightButton % 2;
		case MouseButtons::SCROLL:
			return s_mouseState.middleButton % 2;
		}
		return false;
	}

}
