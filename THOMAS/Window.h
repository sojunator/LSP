#pragma once
#include <Windows.h>
#include "Common.h"
namespace thomas 
{
	class THOMAS_API Window
	{
	private:
		static LRESULT CALLBACK EventHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		static bool UpdateWindow();

	public:
		static bool Init(HINSTANCE hInstance, int nCmdShow, LONG width, LONG height, LPWSTR title);

		static bool SetHeight(LONG height);
		static bool SetWidth(LONG width);
		static bool SetSize(LONG height, LONG width);

		static LONG GetHeight();
		static LONG GetWidth();
		static HWND GetWindowHandler();
		static LONG GetHorizontalResolution();
		static LONG GetVerticalResolution();

		static void ShowCursor();
		static void HideCursor();
		static bool Destroy();
		static bool Initialized();

		static bool ChangeWindowShowState(int nCmdShow);

	private:
		static LONG s_width;
		static LONG s_height;
		static WNDCLASSEX s_windowClassInfo;
		static HWND s_windowHandler;
		static RECT s_windowRectangle;
		static LPWSTR s_title;
		static bool s_initialized;
		static bool s_visibleCursor;
	};
}


