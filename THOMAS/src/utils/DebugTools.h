#pragma once
#include "../../include/AntTweakBar.h"
#include "../ThomasCore.h"

namespace thomas
{
	namespace utils
	{
		class DebugTools
		{

		public:
			static void Init();
			static void Destroy();
			static void RemoveAllVariables();
			static void SetPosition(int x, int y);
			static void AddFloat(void *variable, const char* name);
			static void AddFloatWithStep(void *variable, const char* name, const char *input);
			static void AddInteger(void *variable, const char* name);
			static void AddIntegerWithStep(void *variable, const char* name, const char *input);
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