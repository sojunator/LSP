#pragma once
#include "../../include/AntTweakBar.h"
#include "../ThomasCore.h"

namespace thomas
{
	namespace utils
	{
		class DebugTools
		{
		private:
			static void TW_CALL ReloadShadersButtonCallback(void* clientData);
		public:
			static void Init();
			static void Destroy();
			static void RemoveAllVariables();
			static void SetPosition(int x, int y);
			static void AddFloat(float &variable, const char* name);
			static void AddFloatWithStep(float &variable, const char* name, const char *input);
			static void AddInteger(int &variable, const char* name);
			static void AddIntegerWithStep(int &variable, const char* name, const char *input);
			static void AddBool(bool &variable, const char* name);
			static void AddColor(math::Color  &color, const char* name);
			static void AddDirectionVector(math::Vector3& vector, const char* name);
			static void AddQuaternion(math::Quaternion& quaternion, const char* name);
			static void AddRotation(math::Quaternion& rotation, const char* name);
			static void AddString(std::string& string, const char* name);
			static void Draw();
			static void ToggleVisibility();
			static void Hide();
			static void Show();
			static int ProcessMessages(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static TwBar* GetBar();

		private:
			struct Data
			{
				TwBar *bar;
			};
			static Data s_bar;
			static bool s_visible;
		};

	}
}