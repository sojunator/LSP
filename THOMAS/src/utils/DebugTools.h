#pragma once
#include "../../include/AntTweakBar.h"
#include "../ThomasCore.h"

namespace thomas
{
	namespace utils
	{
		class DebugTools
		{
			struct Data
			{
				TwBar *bar;
			};

		public:
			static bool Init(const char *name);
			static void Destroy();
			static void AddFloat(void *variable, const char* name);
			static void AddFloatWithStep(void *variable, const char* name, const char *input);
			static void AddInteger(void *variable, const char* name);
			static void AddIntegerWithStep(void *variable, const char* name, const char *input);
			static void Draw();

			static int ProcessMessages(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
			static TwBar* GetBar();

		private:
			static Data s_bar;
		};
	}
}
