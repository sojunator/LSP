#include "DebugTools.h"
#include "../graphics/Shader.h"
namespace thomas
{
	namespace utils
	{
		DebugTools::Data DebugTools::s_bar;
		bool DebugTools::s_visible;

		void TW_CALL DebugTools::ReloadShadersButtonCallback(void * clientData)
		{
			graphics::Shader::ReloadShaders();
		}

		void DebugTools::Init()
		{
			TwInit(TW_DIRECT3D11, ThomasCore::GetDevice());
			TwWindowSize(Window::GetWidth(), Window::GetHeight());

			s_bar.bar = TwNewBar("Debug");
			TwDefine("Debug fontsize=3 iconifiable=false");
			Hide();

			TwAddButton(s_bar.bar, "shaderReload", ReloadShadersButtonCallback, NULL, "label='Reload Shaders(F5)' key=F5");
		}

		void DebugTools::Destroy()
		{
			TwTerminate();
		}

		void DebugTools::RemoveAllVariables()
		{
			if (s_bar.bar)
			{
				TwRemoveAllVars(s_bar.bar);
				TwAddButton(s_bar.bar, "shaderReload", ReloadShadersButtonCallback, NULL, "label='Reload Shaders(F5)' key=F5");
			}
			
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

		void DebugTools::AddFloat(float &variable, const char* name)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_FLOAT, &variable, "");
		}

		void DebugTools::AddFloatWithStep(float &variable, const char* name, const char * input)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_FLOAT, &variable, input);
		}

		void DebugTools::AddInteger(int &variable, const char* name)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_INT16, &variable, "");
		}

		void DebugTools::AddIntegerWithStep(int &variable, const char* name, const char * input)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_INT16, &variable, input);
		}

		void DebugTools::AddBool(bool & variable, const char * name)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_BOOL16, &variable, "true='Enabled' false='Disabled'");
		}

		void DebugTools::AddColor(math::Color & color, const char * name)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_COLOR4F, &color, "coloralpha=true");
		}


		void DebugTools::AddDirectionVector(math::Vector3 & vector, const char * name)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_DIR3F, &vector, "");
		}

		void DebugTools::AddQuaternion(math::Quaternion & quaternion, const char * name)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_QUAT4F, &quaternion, "");
		}

		void DebugTools::AddRotation(math::Quaternion & rotation, const char * name)
		{
			AddQuaternion(rotation, name);
		}

		void DebugTools::AddString(std::string & string, const char * name)
		{
			TwAddVarRW(s_bar.bar, name, TW_TYPE_STDSTRING, &string, "");
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
			TwDefine("Debug visible=false");
		}

		void DebugTools::Show()
		{
			s_visible = true;
			TwDefine("Debug visible=true");
		}

	}
}