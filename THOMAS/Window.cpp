#include "Window.h"
#include "Input.h"
namespace thomas 
{
	LONG Window::s_width;
	LONG Window::s_height;
	WNDCLASSEX Window::s_windowClassInfo;
	HWND Window::s_windowHandler;
	RECT Window::s_windowRectangle;
	LPWSTR Window::s_title;
	bool Window::s_initialized;
	bool Window::s_visibleCursor;


	LRESULT CALLBACK Window::EventHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		//If one case is hit the code will execute everything down until a break;
		switch (message)
		{

		case WM_SETFOCUS:
		case WM_KILLFOCUS:
			Input::ProcessGamePad(message, wParam, lParam);
			break;
		case WM_ACTIVATEAPP:
			Input::ProcessKeyboard(message, wParam, lParam);
			Input::ProcessMouse(message, wParam, lParam);
			break;
		case WM_INPUT:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_MOUSEHOVER:
			Input::ProcessMouse(message, wParam, lParam);
			break;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
			Input::ProcessKeyboard(message, wParam, lParam);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	bool Window::UpdateWindow()
	{
		return false;
	}

	bool Window::Init(HINSTANCE hInstance, int nCmdShow, LONG width, LONG height, LPWSTR title)
	{
		if (s_initialized)
			return false;

		s_height = height;
		s_width = width;
		s_title = title;
		s_initialized = false;

		s_windowClassInfo = { 0 };
		s_windowClassInfo.cbSize = sizeof(WNDCLASSEX);
		s_windowClassInfo.style = CS_HREDRAW | CS_VREDRAW;
		s_windowClassInfo.lpfnWndProc = EventHandler; //Callback for EVENTS
		s_windowClassInfo.hInstance = hInstance;
		s_windowClassInfo.lpszClassName = L"ThomasWindow";

		if (!RegisterClassEx(&s_windowClassInfo))
			return false;

		s_windowRectangle = { 0, 0, width, height };

		//Properties for window
		AdjustWindowRect(&s_windowRectangle, WS_OVERLAPPEDWINDOW, FALSE);

		s_windowHandler = CreateWindow(
			L"ThomasWindow",			// CLASS, if does not exists fails!
			title,		// Window name (title)
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			s_windowRectangle.right - s_windowRectangle.left,
			s_windowRectangle.bottom - s_windowRectangle.top,
			nullptr,
			nullptr,
			hInstance,
			nullptr);

		if (s_windowHandler)
		{
			s_initialized = true;
			ChangeWindowShowState(nCmdShow);
		}

		return s_initialized;
	}

	bool Window::SetHeight(LONG height)
	{
		if (height > 0 && height <= GetVerticalResolution())
		{
			s_height = height;
			return UpdateWindow();
		}

		return false;
	}

	bool Window::SetWidth(LONG width)
	{
		if (width > 0 && width <= GetHorizontalResolution())
		{
			s_width = width;
			return UpdateWindow();
		}

		return false;
	}

	bool Window::SetSize(LONG height, LONG width)
	{
		if (SetWidth(width) && SetHeight(height))
		{
			return true;
		}

		return false;
	}

	LONG Window::GetHeight()
	{
		return s_height;
	}

	LONG Window::GetWidth()
	{
		return s_width;
	}

	HWND Window::GetWindowHandler()
	{
		return s_windowHandler;
	}

	LONG Window::GetHorizontalResolution()
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		return desktop.right;
	}

	LONG Window::GetVerticalResolution()
	{
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		return desktop.bottom;
	}

	void Window::ShowCursor()
	{
		s_visibleCursor = true;
		UpdateWindow();
	}

	void Window::HideCursor()
	{
		s_visibleCursor = false;
		UpdateWindow();
	}

	bool Window::Destroy()
	{
		return DestroyWindow(s_windowHandler);
	}

	bool Window::Initialized()
	{
		return s_initialized;
	}

	bool Window::ChangeWindowShowState(int nCmdShow)
	{
		return ShowWindow(s_windowHandler, nCmdShow);
	}



}