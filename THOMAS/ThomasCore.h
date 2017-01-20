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
		static bool Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow, LONG windowWidth, LONG windowHeight);
		
		static HINSTANCE GetHInstance();

		static void Start();
		static bool Initialized();
		static bool Destroy();

	private:
		static HINSTANCE m_hInstance;
		static bool m_initialized;
		static ID3D11Device* s_device;
		static ID3D11DeviceContext* s_context;
		static IDXGISwapChain* s_swapchain;

	};
}