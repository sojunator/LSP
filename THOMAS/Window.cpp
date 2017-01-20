#include "Window.h"
#include "Input.h"
namespace thomas 
{
	LONG Window::m_width;
	LONG Window::m_height;
	WNDCLASSEX Window::m_windowClassInfo;
	HWND Window::m_windowHandler;
	RECT Window::m_windowRectangle;
	LPWSTR Window::m_title;
	bool Window::m_initialized;
	bool Window::m_visibleCursor;


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
		if (m_initialized)
			return false;

		m_height = height;
		m_width = width;
		m_title = title;
		m_initialized = false;

		m_windowClassInfo = { 0 };
		m_windowClassInfo.cbSize = sizeof(WNDCLASSEX);
		m_windowClassInfo.style = CS_HREDRAW | CS_VREDRAW;
		m_windowClassInfo.lpfnWndProc = EventHandler; //Callback for EVENTS
		m_windowClassInfo.hInstance = hInstance;
		m_windowClassInfo.lpszClassName = L"ThomasWindow";

		if (!RegisterClassEx(&m_windowClassInfo))
			return false;

		m_windowRectangle = { 0, 0, width, height };

		//Properties for window
		AdjustWindowRect(&m_windowRectangle, WS_OVERLAPPEDWINDOW, FALSE);

		m_windowHandler = CreateWindow(
			L"ThomasWindow",			// CLASS, if does not exists fails!
			title,		// Window name (title)
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			m_windowRectangle.right - m_windowRectangle.left,
			m_windowRectangle.bottom - m_windowRectangle.top,
			nullptr,
			nullptr,
			hInstance,
			nullptr);

		if (m_windowHandler)
		{
			m_initialized = true;
			ChangeWindowShowState(nCmdShow);
		}

		return m_initialized;
	}

	bool Window::SetHeight(LONG height)
	{
		if (height > 0 && height <= GetVerticalResolution())
		{
			m_height = height;
			return UpdateWindow();
		}

		return false;
	}

	bool Window::SetWidth(LONG width)
	{
		if (width > 0 && width <= GetHorizontalResolution())
		{
			m_width = width;
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
		return m_height;
	}

	LONG Window::GetWidth()
	{
		return m_width;
	}

	HWND Window::GetWindowHandler()
	{
		return m_windowHandler;
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
		m_visibleCursor = true;
		UpdateWindow();
	}

	void Window::HideCursor()
	{
		m_visibleCursor = false;
		UpdateWindow();
	}

	bool Window::Destroy()
	{
		return DestroyWindow(m_windowHandler);
	}

	bool Window::Initialized()
	{
		return m_initialized;
	}

	bool Window::ChangeWindowShowState(int nCmdShow)
	{
		return ShowWindow(m_windowHandler, nCmdShow);
	}



}
