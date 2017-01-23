#pragma once
#include "Common.h"
#include "Window.h"
#include <d3d11.h>
#include <d3dcompiler.h>

namespace thomas
{
	class THOMAS_API ThomasCore
	{
	private:
		static void Update();
	public:
		static bool Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, LONG windowWidth, LONG windowHeight, LPWSTR title);
		
		static HINSTANCE GetHInstance();

		static void Start();
		static bool Initialized();
		static bool Destroy();

	private:
		static HINSTANCE s_hInstance;
		static bool s_initialized;

	};
}