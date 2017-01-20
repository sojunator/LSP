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

		public:
			static bool Init(LONG width, LONG height, ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle);

		private:

		};
	}

}