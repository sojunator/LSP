#pragma once
#include "d3d.h"

namespace thomas {
	namespace utils
	{
		bool D3d::Init(LONG width, LONG height, ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle)
		{
			return SwapchainAndDevice(width, height, device, context, swapchain, handle);
			
		}

		bool D3d::SwapchainAndDevice(LONG width, LONG height, ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle)
		{
			HRESULT hr;
			DXGI_SWAP_CHAIN_DESC scd;
			ZeroMemory(&scd, sizeof(scd));

			scd.BufferCount = 1;
			scd.BufferDesc.Height = (float)height;
			scd.BufferDesc.Width = (float)width;
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			scd.OutputWindow = handle;
			scd.SampleDesc.Count = 1; // AA times 1
			scd.SampleDesc.Quality = 0;
			scd.Windowed = TRUE;
			scd.BufferDesc.RefreshRate.Numerator = 0; // change 0 to numerator for vsync
			scd.BufferDesc.RefreshRate.Denominator = 1; // change 1 to denominator for vynsc

			hr = D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				NULL,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&scd,
				&swapchain,
				&device,
				NULL,
				&context);

			if (FAILED(hr))
			{
				MessageBox(handle, L"Failed to init swapchain", L"Fatal error", MB_OK);
				return false;
			}
			
			return true;
		}
	}
}