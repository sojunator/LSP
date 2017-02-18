#include "DebugTools.h"

namespace thomas
{
	namespace utils
	{
		DebugTools::Data DebugTools::s_bar;
		bool DebugTools::s_visible;
		void DebugTools::Init()
		{
			TwInit(TW_DIRECT3D11, ThomasCore::GetDevice());
			TwWindowSize(Window::GetWidth(), Window::GetHeight());

			s_bar.bar = TwNewBar("Main");
			TwDefine(" Main label='Debug Variables' fontSize=3 position='30 150' size='270 440' valuesWidth=100");
			Hide();
		}

		void DebugTools::Destroy()
		{
			TwTerminate();
		}

		void DebugTools::RemoveAllVariables()
		{
			
			TwDeleteBar(s_bar.bar);
			s_bar.bar = TwNewBar("Main");
			Hide();
		}

		void DebugTools::SetPosition(int x, int y)
		{
			/*int barPos[2] = { x, y };
			TwSetParam(s_bar.bar, NULL, "position", TW_PARAM_INT32, 2, &barPos);*/
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

		void DebugTools::ToggleVisibility()
		{
			s_visible = !s_visible;
			if (s_visible)
				Show();
			else
				Hide();
		}

		void DebugTools::Hide()
		{
			s_visible = false;
			TwDefine("Main visible=false");
		}

		void DebugTools::Show()
		{
			s_visible = true;
			TwDefine("Main visible=true");
		}

	}
}