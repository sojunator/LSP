#include "DebugTools.h"

namespace thomas
{
	namespace utils
	{
		DebugTools::Data DebugTools::s_bar;

		bool DebugTools::Init(const char *name)
		{
			TwInit(TW_DIRECT3D11, ThomasCore::GetDevice()); // for Direct3D 11
			TwWindowSize(Window::GetWidth(), Window::GetHeight());
			s_bar.bar = TwNewBar(name);
			return true;
		}

		void DebugTools::Destroy()
		{
			TwTerminate();
		}

		int DebugTools::ProcessMessages(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			TwEventWin(hWnd, message, wParam, lParam);
			return 0;
		}

		TwBar* DebugTools::GetBar()
		{
			return s_bar.bar;
		}

		void DebugTools::AddFloat(void *variable, const char* name)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_FLOAT, variable, "");
		}

		void DebugTools::AddFloatWithStep(void *variable, const char* name, const char * input)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_FLOAT, variable, input);
		}

		void DebugTools::AddInteger(void *variable, const char* name)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_INT16, variable, "");
		}

		void DebugTools::AddIntegerWithStep(void *variable, const char* name, const char * input)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_INT16, variable, input);
		}

		void DebugTools::Draw()
		{
			TwDraw();
		}

	}
}