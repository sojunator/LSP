#pragma once
#include "Common.h"
#include "Window.h"
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


	private:
		static HINSTANCE m_hInstance;
		static bool m_initialized;

	};
}