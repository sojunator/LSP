#pragma once
#include "d3d.h"
#include <AtlBase.h>
#include <atlconv.h>
#include "Math.h"
namespace thomas
{
	namespace utils
	{
		ID3D11RenderTargetView* D3d::s_backBuffer;
		ID3D11RasterizerState* D3d::s_rasterState;
		bool D3d::Init(ID3D11Device*& device, ID3D11DeviceContext*& context, 
			IDXGISwapChain*& swapchain, ID3D11Debug*& debug)
		{
			LOG("Initiating DirectX");

			if (!CreateSwapchainAndDeviceAndContext(Window::GetWidth(), Window::GetHeight(), device, context, swapchain, Window::GetWindowHandler()))
				return false;

			if (!CreateSwapChainTexture(device, swapchain))
				return false;


			#ifdef _DEBUG
			debug = CreateDebug();
			if (debug == nullptr)
				return false;
			#endif

			////Set back buffer texture 
			context->OMSetRenderTargets(1, &s_backBuffer, NULL);
			CreateViewPort(context, Window::GetHeight(), Window::GetWidth());
			s_rasterState = CreateRasterizer();

			LOG("DirectX initiated, welcome to the masterace");
			return true;
		}

		bool D3d::CreateSwapchainAndDeviceAndContext(LONG width, LONG height, ID3D11Device*& device, 
			ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle)
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
			scd.Flags = 0;
			scd.SampleDesc.Count = 1; // AA times 1
			scd.SampleDesc.Quality = 0;
			scd.Windowed = TRUE;
			scd.BufferDesc.RefreshRate.Numerator = 0; // change 0 to numerator for vsync
			scd.BufferDesc.RefreshRate.Denominator = 0; // change 1 to denominator for vynsc

			
			hr = D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				#ifdef _DEBUG
					D3D11_CREATE_DEVICE_DEBUG,
				#else
					NULL,
				#endif // _DEBUG
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
				LOG_HR(hr);
				return false;
			}

			return true;

		}

		bool D3d::CreateSwapChainTexture(ID3D11Device * device, IDXGISwapChain * swapchain)
		{
			HRESULT hr;
			ID3D11Texture2D* pbackBuffer;
			hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pbackBuffer);

			if (FAILED(hr))
			{
				LOG_HR(hr);
				return false;
			}

			s_backBuffer = CreateRenderTargetViewFromBuffer(device, pbackBuffer);
			pbackBuffer->Release(); // not needed anymore, its on the gpu

			if (FAILED(hr))
			{
				LOG_HR(hr);
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
		bool D3d::CreateDepthStencilState(ID3D11Device * device, ID3D11DepthStencilState*& stencil)
		{
			CD3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

			depthStencilDesc.DepthEnable = true;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
			depthStencilDesc.StencilReadMask = true;
			depthStencilDesc.StencilWriteMask = 0xFF;
			depthStencilDesc.StencilReadMask = 0xFF;

			// if front face
			depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			// if back face
			depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			HRESULT hr = device->CreateDepthStencilState(&depthStencilDesc, &stencil);
			if (FAILED(hr))
			{
				LOG_HR(hr);
				return false;
			}
			return true;
		}
		
		bool D3d::CreateDepthStencilView(ID3D11Device * device, ID3D11DepthStencilView *& stencilView, 
			ID3D11Texture2D*& depthBuffer)
		{
			D3D11_TEXTURE2D_DESC depthBufferDesc;
			D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;

			ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));
			ZeroMemory(&depthViewDesc, sizeof(depthViewDesc));

			// Z-buffer texture desc
			depthBufferDesc.Width = Window::GetWidth();
			depthBufferDesc.Height = Window::GetHeight();
			depthBufferDesc.MipLevels = 1;
			depthBufferDesc.ArraySize = 1;
			depthBufferDesc.Format = DXGI_FORMAT_R32_TYPELESS;
			depthBufferDesc.SampleDesc.Count = 1;
			depthBufferDesc.SampleDesc.Quality = 0;
			depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthBufferDesc.CPUAccessFlags = 0;
			depthBufferDesc.MiscFlags = 0;
		

			// Z-buffer view desc
			depthViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
			depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			depthViewDesc.Texture2D.MipSlice = 0;
			depthViewDesc.Flags = 0;

			HRESULT hr = device->CreateTexture2D(&depthBufferDesc, NULL, &depthBuffer);
			if (FAILED(hr))
			{
				LOG_HR(hr);
				depthBuffer = nullptr;
				return false;
			}

			hr = device->CreateDepthStencilView(depthBuffer, &depthViewDesc, &stencilView);
			if (FAILED(hr))
			{
				LOG_HR(hr);
				stencilView = nullptr;
				return false;
			}

			return true;
			
		}
		ID3D11Debug * D3d::CreateDebug()
		{
			ID3D11Debug* debug;
			HRESULT hr = ThomasCore::GetDevice()->QueryInterface(IID_PPV_ARGS(&debug));
			if (FAILED(hr))
			{
				LOG_HR(hr);
				return nullptr;
			}
			return debug;
		}
		void D3d::PresentBackBuffer(ID3D11DeviceContext *& context, IDXGISwapChain *& swapchain)
		{
			HRESULT hr = swapchain->Present(0, 0);
			if (FAILED(hr))
			{
				LOG_HR(hr);
			}
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

		bool D3d::LoadTextureFromFile(ID3D11Device* device, ID3D11DeviceContext* context, std::string fileName, 
			ID3D11Resource*& texture, ID3D11ShaderResourceView*& textureView)
		{
			// Convert from string to char in order to split by token
			// convert back from char, since its easier to compare strings than chars
			// Fuck you, thats why.
			char* filename_c = new char[fileName.length() + 1];
			std::strcpy(filename_c, fileName.c_str());

			char * extension_char = PathFindExtensionA(filename_c);
			std::string extension_string(extension_char);

			delete[] filename_c;

			HRESULT hr;
			if (extension_string == ".dds")
			{
				hr = DirectX::CreateDDSTextureFromFile(device, context, CA2W(fileName.c_str()), &texture, &textureView);
			}
			else
			{
				hr = DirectX::CreateWICTextureFromFile(device, context, CA2W(fileName.c_str()), &texture, &textureView);
			}

			if (FAILED(hr))
			{
				LOG_HR(hr);
				return false;
			}
	
			return true;
		}

		bool D3d::Destroy()
		{
			s_backBuffer->Release();
			s_backBuffer = 0;
			s_rasterState->Release();
			s_rasterState = 0;

			return true;
		}

		ID3D11RenderTargetView * D3d::CreateRenderTargetViewFromBuffer(ID3D11Device* device, 
			ID3D11Resource * buffer)
		{
			ID3D11RenderTargetView* rtv;
			D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;

			ZeroMemory(&rtvDesc, sizeof(rtvDesc));
			rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			rtvDesc.Texture2D.MipSlice = 0;

			HRESULT hr = device->CreateRenderTargetView(buffer, &rtvDesc, &rtv);
			if (FAILED(hr))
			{
				LOG_HR(hr);
				return nullptr;
			}

			return rtv;
		}


		ID3D11RasterizerState * D3d::CreateRasterizer()
		{
			ID3D11RasterizerState* rasterState;
			D3D11_RASTERIZER_DESC rasterDesc;

			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = D3D11_CULL_BACK;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = false;
			rasterDesc.FillMode = D3D11_FILL_SOLID;
			rasterDesc.FrontCounterClockwise = true;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			ThomasCore::GetDevice()->CreateRasterizerState(&rasterDesc, &rasterState);

			return rasterState;
		}
	}
}