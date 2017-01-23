#pragma once
#include "d3d.h"

namespace thomas {
	namespace utils
	{
		ID3D11RenderTargetView* D3d::s_backBuffer;

		bool D3d::Init(LONG width, LONG height, ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle)
		{
			if (!SwapchainAndDevice(width, height, device, context, swapchain, handle))
				return false;
			if (!CreateSwapChainTexture(device, swapchain))
				return false;

			////Set back buffer texture 
			context->OMSetRenderTargets(1, &s_backBuffer, NULL);
			CreateViewPort(context, height, width);

			return true;

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
				D3D11_CREATE_DEVICE_DEBUG,
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

		bool D3d::CreateSwapChainTexture(ID3D11Device *& device, IDXGISwapChain *& swapchain)
		{
			HRESULT hr;
			ID3D11Texture2D* pbackBuffer;
			hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pbackBuffer);

			if (FAILED(hr))
			{
				MessageBox(NULL, L"Failed to get backbuffer", L"Fatal error", MB_OK);
				return false;
			}

			hr = device->CreateRenderTargetView(pbackBuffer, NULL, &s_backBuffer); // Move it to the gpu
			pbackBuffer->Release(); // not needed anymore, its on the gpu

			if (FAILED(hr))
			{
				MessageBox(NULL, L"Failed to move backbuffer to GPU", L"Fatal error", MB_OK);
				return false;
			}
			return true;
		}

		void D3d::CreateViewPort(ID3D11DeviceContext *& context, LONG height, LONG width)
		{
			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(viewport));
			
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Height = height;
			viewport.Width = width;

			context->RSSetViewports(1, &viewport);
		}
		void D3d::PresentBackBuffer(ID3D11DeviceContext *& context, IDXGISwapChain *& swapchain)
		{
			float color[4] = { 0.3f, 0.4f, 0.3f, 1.0f };
			context->ClearRenderTargetView(s_backBuffer, color);
			swapchain->Present(0, 0);
		}

		bool D3d::Destroy()
		{
			s_backBuffer->Release();
			s_backBuffer = 0;

			return true;
		}
	}
}