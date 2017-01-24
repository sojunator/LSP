#pragma once
#include "d3d.h"
#include "../ThomasCore.h"
#include "Math.h"
namespace thomas
{
	namespace utils
	{
		ID3D11RenderTargetView* D3d::s_backBuffer;
		ID3D11RasterizerState* D3d::s_rasterState;
		bool D3d::Init(LONG width, LONG height, ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle)
		{
			LOG("Initiating DirectX");
			if (!SwapchainAndDevice(width, height, device, context, swapchain, handle))
				return false;
			if (!CreateSwapChainTexture(device, swapchain))
				return false;

			////Set back buffer texture 
			context->OMSetRenderTargets(1, &s_backBuffer, NULL);
			CreateViewPort(context, height, width);


			s_rasterState = CreateRasterizer();

			LOG("DirectX initiated, welcome to the masterace");
			return true;

		}

		bool D3d::SwapchainAndDevice(LONG width, LONG height, ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle)
		{
			HRESULT hr;
			DXGI_SWAP_CHAIN_DESC scd;
			ZeroMemory(&scd, sizeof(scd));

			scd.BufferCount = 2;
			scd.BufferDesc.Height = (float)height;
			scd.BufferDesc.Width = (float)width;
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			scd.OutputWindow = handle;
			scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // we recommend using this swap effect for all applications
			scd.Flags = 0;
			scd.SampleDesc.Count = 1; // AA times 1
			scd.SampleDesc.Quality = 0;
			scd.Windowed = TRUE;
			scd.BufferDesc.RefreshRate.Numerator = 0; // change 0 to numerator for vsync
			scd.BufferDesc.RefreshRate.Denominator = 0; // change 1 to denominator for vynsc

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
				LOG("Could not create device or swapchain or context");
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
				LOG("Failed to get backbuffer");
				return false;
			}

			hr = device->CreateRenderTargetView(pbackBuffer, NULL, &s_backBuffer); // Move it to the gpu
			pbackBuffer->Release(); // not needed anymore, its on the gpu

			if (FAILED(hr))
			{
				LOG("Failed to move backbuffer to GPU Fatal error");
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


			
			HRESULT t = swapchain->Present(0, 0);

		}

		bool D3d::Clear()
		{
			float color[4] = { 0.3f, 0.4f, 0.3f, 1.0f };
			ThomasCore::GetDeviceContext()->ClearRenderTargetView(s_backBuffer, color);

			math::Viewport vp(0, 0, Window::GetWidth(), Window::GetHeight());
			ThomasCore::GetDeviceContext()->RSSetViewports(1, vp.Get11());
			ThomasCore::GetDeviceContext()->RSSetState(s_rasterState);

			return true;
		}

		bool D3d::LoadTextureFromFile(ID3D11Device*& device, ID3D11DeviceContext*& context, wchar_t* fileName, _In_opt_ ID3D11Resource** texture, ID3D11ShaderResourceView** textureView, size_t size)
		{
			HRESULT hr = DirectX::CreateWICTextureFromFile(device, context, fileName, texture, textureView, size);
			if (FAILED(hr))
			{
				LOG("Could not create texture");
				return false;
			}
			return true;
		}

		bool D3d::Destroy()
		{
			s_backBuffer->Release();
			s_backBuffer = 0;

			return true;
		}

		ID3D11Buffer * D3d::CreateVertexBuffer(UINT size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA * data, ID3D11Device * device)
		{
			return CreateBuffer(size, dynamic, streamout, data, device, D3D11_BIND_VERTEX_BUFFER);
		}

		ID3D11Buffer * D3d::CreateIndexBuffer(UINT size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA * data, ID3D11Device * device)
		{
			return CreateBuffer(size, dynamic, streamout, data, device, D3D11_BIND_INDEX_BUFFER);
		}

		ID3D11Buffer* D3d::CreateBuffer(UINT size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA * data, ID3D11Device * device, D3D11_BIND_FLAG bindFlag)
		{
			D3D11_BUFFER_DESC bufferDesc;
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));
			bufferDesc.ByteWidth = size;
			bufferDesc.MiscFlags = 0;

			if (streamout)
			{

				bufferDesc.BindFlags = bindFlag | D3D11_BIND_STREAM_OUTPUT;
			}
			else
			{
				bufferDesc.BindFlags = bindFlag;
			}

			if (dynamic)
			{
				bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
			}
			else
			{
				bufferDesc.CPUAccessFlags = 0;
				bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			}

			ID3D11Buffer * buffer = 0;
			HRESULT hr = device->CreateBuffer(&bufferDesc, data, &buffer);

			if (FAILED(hr))
			{
				LOG("Failed to create vertex buffer");
				return nullptr;
			}

			return buffer;
		}

		ID3D11RasterizerState * D3d::CreateRasterizer()
		{
			ID3D11RasterizerState* rasterState;

			D3D11_RASTERIZER_DESC rasterDesc;
			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = D3D11_CULL_NONE;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = false;
			rasterDesc.FillMode = D3D11_FILL_SOLID;
			rasterDesc.FrontCounterClockwise = false;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			ThomasCore::GetDevice()->CreateRasterizerState(&rasterDesc, &rasterState);

			return rasterState;

		}



	}
}