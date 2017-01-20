#pragma once
#include "../Common.h"
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")

namespace thomas {
	namespace utils
	{
		class THOMAS_API D3d
		{
		private:
			static bool SwapchainAndDevice(LONG witdh, LONG height, ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle);
			static bool CreateSwapChainTexture(ID3D11Device*& device, IDXGISwapChain*& swapchain);
			static void CreateViewPort(ID3D11DeviceContext*& context, LONG height, LONG width);

		public:
			static bool Init(LONG width, LONG height, ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle);
			static void PresentBackBuffer(ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain);
			static bool Destroy();

		private:
			static ID3D11RenderTargetView* s_backBuffer;

		};
	}

}