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

	DirectX::Keyboard::KeyboardStateTracker Input::s_keyboardTracker;
	DirectX::Mouse::ButtonStateTracker Input::s_mouseTracker;
	DirectX::GamePad::ButtonStateTracker Input::s_gamePadTracker;

	bool Input::s_initialized;

	bool Input::Init()
	{
		s_keyboard = std::make_unique<DirectX::Keyboard>();
		s_mouse = std::make_unique<DirectX::Mouse>();
		s_gamePad = std::make_unique<DirectX::GamePad>();

		s_mouse->SetWindow(Window::GetWindowHandler());
		s_initialized = Window::Initialized();
		LOG("Initiating Input");
		return s_initialized;
	}

	void Input::Update()
	{
		if (s_initialized)
		{
			s_keyboardState = s_keyboard->GetState();
			s_gamePadState = s_gamePad->GetState(0);
			s_mouseState = s_mouse->GetState();

			s_keyboardTracker.Update(s_keyboardState);
			s_mouseTracker.Update(s_mouseState);
			s_gamePadTracker.Update(s_gamePadState);
		}

	}

	void Input::ProcessKeyboard(UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (s_initialized)
			s_keyboard->ProcessMessage(message, wParam, lParam);
	}

	void Input::ProcessMouse(UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (s_initialized)
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


	//gamePad
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

	bool Input::GetButtonDown(Buttons button)
	{
		if (!s_gamePadState.IsConnected()) //Always false if no gamePad.
			return false;
		switch (button)
		{
		case Buttons::A:
			return (s_gamePadTracker.a == s_gamePadTracker.PRESSED);
		case Buttons::B:
			return (s_gamePadTracker.b == s_gamePadTracker.PRESSED);
		case Buttons::X:
			return (s_gamePadTracker.x == s_gamePadTracker.PRESSED);
		case Buttons::Y:
			return (s_gamePadTracker.y == s_gamePadTracker.PRESSED);
		case Buttons::DPAD_UP:
			return (s_gamePadTracker.dpadUp == s_gamePadTracker.PRESSED);
		case Buttons::DPAD_DOWN:
			return (s_gamePadTracker.dpadDown == s_gamePadTracker.PRESSED);
		case Buttons::DPAD_LEFT:
			return (s_gamePadTracker.dpadLeft == s_gamePadTracker.PRESSED);
		case Buttons::DPAD_RIGHT:
			return (s_gamePadTracker.dpadRight == s_gamePadTracker.PRESSED);
		case Buttons::LS:
			return (s_gamePadTracker.leftStick == s_gamePadTracker.PRESSED);
		case Buttons::RS:
			return (s_gamePadTracker.rightStick == s_gamePadTracker.PRESSED);
		case Buttons::LB:
			return (s_gamePadTracker.leftShoulder == s_gamePadTracker.PRESSED);
		case Buttons::RB:
			return (s_gamePadTracker.rightShoulder == s_gamePadTracker.PRESSED);
		case Buttons::LT:
			return (s_gamePadTracker.leftTrigger == s_gamePadTracker.PRESSED);
		case Buttons::RT:
			return (s_gamePadTracker.rightTrigger == s_gamePadTracker.PRESSED);
		case Buttons::START:
			return (s_gamePadTracker.start == s_gamePadTracker.PRESSED);
		case Buttons::BACK:
			return (s_gamePadTracker.back == s_gamePadTracker.PRESSED);

		}
		return false;
	}

	bool Input::GetButtonUp(Buttons button)
	{
		if (!s_gamePadState.IsConnected()) //Always false if no gamePad.
			return false;
		switch (button)
		{
		case Buttons::A:
			return (s_gamePadTracker.a == s_gamePadTracker.RELEASED);
		case Buttons::B:
			return (s_gamePadTracker.b == s_gamePadTracker.RELEASED);
		case Buttons::X:
			return (s_gamePadTracker.x == s_gamePadTracker.RELEASED);
		case Buttons::Y:
			return (s_gamePadTracker.y == s_gamePadTracker.RELEASED);
		case Buttons::DPAD_UP:
			return (s_gamePadTracker.dpadUp == s_gamePadTracker.RELEASED);
		case Buttons::DPAD_DOWN:
			return (s_gamePadTracker.dpadDown == s_gamePadTracker.RELEASED);
		case Buttons::DPAD_LEFT:
			return (s_gamePadTracker.dpadLeft == s_gamePadTracker.RELEASED);
		case Buttons::DPAD_RIGHT:
			return (s_gamePadTracker.dpadRight == s_gamePadTracker.RELEASED);
		case Buttons::LS:
			return (s_gamePadTracker.leftStick == s_gamePadTracker.RELEASED);
		case Buttons::RS:
			return (s_gamePadTracker.rightStick == s_gamePadTracker.RELEASED);
		case Buttons::LB:
			return (s_gamePadTracker.leftShoulder == s_gamePadTracker.RELEASED);
		case Buttons::RB:
			return (s_gamePadTracker.rightShoulder == s_gamePadTracker.RELEASED);
		case Buttons::LT:
			return (s_gamePadTracker.leftTrigger == s_gamePadTracker.RELEASED);
		case Buttons::RT:
			return (s_gamePadTracker.rightTrigger == s_gamePadTracker.RELEASED);
		case Buttons::START:
			return (s_gamePadTracker.start == s_gamePadTracker.RELEASED);
		case Buttons::BACK:
			return (s_gamePadTracker.back == s_gamePadTracker.RELEASED);

		}
		return false;
	}

	bool Input::GetButton(Buttons button)
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
		case Buttons::START:
			return s_gamePadState.IsStartPressed();
		case Buttons::BACK:
			return s_gamePadState.IsBackPressed();

		}
		return false;
	}

	//mouse

	LONG Input::GetMouseY()
	{
		return s_mouseState.y;
	}

	LONG Input::GetMouseX()
	{
		return s_mouseState.x;
	}

	bool Input::GetMouseButtonDown(MouseButtons button)
	{
		switch (button)
		{
		case MouseButtons::LEFT:
			return (s_mouseTracker.leftButton == s_mouseTracker.PRESSED);
		case MouseButtons::RIGHT:
			return (s_mouseTracker.rightButton == s_mouseTracker.PRESSED);
		case MouseButtons::MIDDLE:
			return (s_mouseTracker.middleButton == s_mouseTracker.PRESSED);
		}
		return false;
	}

	bool Input::GetMouseButtonUP(MouseButtons button)
	{
		switch (button)
		{
		case MouseButtons::LEFT:
			return (s_mouseTracker.leftButton == s_mouseTracker.RELEASED);
		case MouseButtons::RIGHT:
			return (s_mouseTracker.rightButton == s_mouseTracker.RELEASED);
		case MouseButtons::MIDDLE:
			return (s_mouseTracker.middleButton == s_mouseTracker.RELEASED);
		}
		return false;
	}

	bool Input::GetMouseButton(MouseButtons button)
	{
		switch (button)
		{
		case MouseButtons::LEFT:
			return s_mouseState.leftButton;
		case MouseButtons::RIGHT:
			return s_mouseState.rightButton;
		case MouseButtons::MIDDLE:
			return s_mouseState.middleButton;
		}
		return false;
	}


	//keyboard

	bool Input::GetKeyDown(Keys key)
	{
		return s_keyboardTracker.IsKeyPressed((DirectX::Keyboard::Keys)key);
	}

	bool Input::GetKeyUp(Keys key)
	{
		return s_keyboardTracker.IsKeyReleased((DirectX::Keyboard::Keys)key);
	}

	bool Input::GetKey(Keys key)
	{
		return s_keyboardState.IsKeyDown((DirectX::Keyboard::Keys)key);
	}




}