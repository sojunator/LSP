#pragma once
#include "d3d.h"
#include <AtlBase.h>
#include <atlconv.h>
#include "Math.h"
namespace thomas
{
	namespace utils
	{
		bool D3d::CreateRenderTargetView(ID3D11RenderTargetView *& rtv, ID3D11ShaderResourceView *& srv)
		{
			D3D11_TEXTURE2D_DESC textureDesc;
			ZeroMemory(&textureDesc, sizeof(textureDesc));
			textureDesc.Width = Window::GetWidth();
			textureDesc.Height = Window::GetHeight();
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.SampleDesc.Quality = 0;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;//D3D11_RESOURCE_MISC_GENERATE_MIPS;

			D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
			ZeroMemory(&viewDesc, sizeof(viewDesc));
			viewDesc.Format = textureDesc.Format;
			viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			viewDesc.Texture2D.MipLevels = 1;
			viewDesc.Texture2D.MostDetailedMip = 0;

			ID3D11Texture2D* quadTexture;

			ThomasCore::GetDevice()->CreateTexture2D(&textureDesc, NULL, &quadTexture);
			ThomasCore::GetDevice()->CreateShaderResourceView(quadTexture, &viewDesc, &srv);
			ThomasCore::GetDevice()->CreateRenderTargetView(quadTexture, NULL, &rtv);
			quadTexture->Release();
			
			return true;
		}
		bool D3d::Init(ID3D11Device*& device, ID3D11DeviceContext*& context,
			IDXGISwapChain*& swapchain, ID3D11Debug*& debug)
		{
			LOG("Initiating DirectX");

			if (!CreateSwapchainAndDeviceAndContext(Window::GetWidth(), Window::GetHeight(), device, context, swapchain, Window::GetWindowHandler()))
				return false;

			

			#ifdef _DEBUG
			debug = CreateDebug();
			if (debug == nullptr)
				return false;
			#endif

		

			
			LOG("DirectX initiated, welcome to the masterace");
			return true;
		}

		bool D3d::CreateSwapchainAndDeviceAndContext(LONG width, LONG height, ID3D11Device*& device, 
			ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle)
		{
			HRESULT hr;
			DXGI_SWAP_CHAIN_DESC scd;
			ZeroMemory(&scd, sizeof(scd));

			scd.BufferCount = 1;
			scd.BufferDesc.Height = (float)height;
			scd.BufferDesc.Width = (float)width;
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
			scd.OutputWindow = handle;
			scd.Flags = 0;
			
			scd.SampleDesc.Count = 1; // AA times 1
			scd.SampleDesc.Quality = 0;
			scd.Windowed = TRUE;
			scd.BufferDesc.RefreshRate.Numerator = 0; // change 0 to numerator for vsync
			scd.BufferDesc.RefreshRate.Denominator = 1; // change 1 to denominator for vynsc
			
			
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

		bool D3d::CreateBackBuffer(ID3D11Device * device, IDXGISwapChain * swapchain, ID3D11RenderTargetView*& backBuffer, ID3D11ShaderResourceView*& backbufferSRV)
		{
			HRESULT hr;
			ID3D11Texture2D* pbackBuffer;
			hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pbackBuffer);


			D3D11_TEXTURE2D_DESC backBufferDesc;
			pbackBuffer->GetDesc(&backBufferDesc);
			if (FAILED(hr))
			{
				LOG_HR(hr);
				return false;
			}

			hr = device->CreateRenderTargetView(pbackBuffer, NULL, &backBuffer);

			if (FAILED(hr))
			{
				LOG_HR(hr);
				return false;
			}

			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			srvDesc.Format = backBufferDesc.Format;
			srvDesc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = backBufferDesc.MipLevels;

			hr = device->CreateShaderResourceView(pbackBuffer, NULL, &backbufferSRV);

			if (FAILED(hr))
			{
				LOG_HR(hr);
				return false;
			}

			return true;
		}

	
		ID3D11DepthStencilState* D3d::CreateDepthStencilState(D3D11_COMPARISON_FUNC func, bool depth)
		{
			ID3D11DepthStencilState* stencilState;
			CD3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

			depthStencilDesc.DepthEnable = depth;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = func;
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

			HRESULT hr = ThomasCore::GetDevice()->CreateDepthStencilState(&depthStencilDesc, &stencilState);
			if (FAILED(hr))
			{
				LOG_HR(hr);
				return NULL;
			}
			return stencilState;
		}
		
		bool D3d::CreateDepthStencilView(ID3D11Device * device, ID3D11DepthStencilView *& stencilView, 
			ID3D11ShaderResourceView *& depthBufferSRV)
		{
			D3D11_TEXTURE2D_DESC depthStencilBufferDesc;
			D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc;

			ZeroMemory(&depthStencilBufferDesc, sizeof(depthStencilBufferDesc));
			ZeroMemory(&depthViewDesc, sizeof(depthViewDesc));

			// Z-buffer texture desc
			depthStencilBufferDesc.Width = Window::GetWidth();
			depthStencilBufferDesc.Height = Window::GetHeight();
			depthStencilBufferDesc.MipLevels = 1;
			depthStencilBufferDesc.ArraySize = 1;
			depthStencilBufferDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
			depthStencilBufferDesc.SampleDesc.Count = 1;
			depthStencilBufferDesc.SampleDesc.Quality = 0;
			depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
			depthStencilBufferDesc.CPUAccessFlags = 0;
			depthStencilBufferDesc.MiscFlags = 0;
		

			// Z-buffer view desc
			depthViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			depthViewDesc.Texture2D.MipSlice = 0;
			depthViewDesc.Flags = 0;

			ID3D11Texture2D* depthStencilBuffer;

			HRESULT hr = device->CreateTexture2D(&depthStencilBufferDesc, NULL, &depthStencilBuffer);
			if (FAILED(hr))
			{
				LOG_HR(hr);
				return false;
			}

			hr = device->CreateDepthStencilView(depthStencilBuffer, &depthViewDesc, &stencilView);
			if (FAILED(hr))
			{
				LOG_HR(hr);
				stencilView = nullptr;
				return false;
			}

			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
			ZeroMemory(&srvDesc, sizeof(srvDesc));
			srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = 0;
			srvDesc.Texture2D.MipLevels = -1;

			hr = device->CreateShaderResourceView(depthStencilBuffer, &srvDesc, &depthBufferSRV);
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




		bool D3d::InitRenderer(ID3D11RenderTargetView *& backBuffer, ID3D11ShaderResourceView *& backBufferSRV, ID3D11DepthStencilState *& depthStencilState, ID3D11DepthStencilView *& depthStencilView, ID3D11ShaderResourceView *& depthBufferSRV)
		{
			CreateBackBuffer(ThomasCore::GetDevice(), ThomasCore::GetSwapChain(), backBuffer, backBufferSRV);
			CreateDepthStencilView(ThomasCore::GetDevice(), depthStencilView, depthBufferSRV);
		
			depthStencilState = CreateDepthStencilState(D3D11_COMPARISON_LESS, true);


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
				LOG("Failed to load texture: " << fileName);
				LOG_HR(hr);
				return false;
			}
	
			return true;
		}

		bool D3d::LoadCubeTextureFromFile(ID3D11Device * device, ID3D11DeviceContext * context, std::string fileName, ID3D11Resource *& texture, ID3D11ShaderResourceView *& textureView)
		{
			char* filename_c = new char[fileName.length() + 1];
			std::strcpy(filename_c, fileName.c_str());

			char * extension_char = PathFindExtensionA(filename_c);
			std::string extension_string(extension_char);

			delete[] filename_c;

			HRESULT hr;
			if (extension_string == ".dds")
			{
				hr = DirectX::CreateDDSTextureFromFileEx(device, CA2W(fileName.c_str()), 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0,
					D3D11_RESOURCE_MISC_TEXTURECUBE, false, (ID3D11Resource**)&texture, &textureView, nullptr);
			}
	
			if (FAILED(hr))
			{
				LOG("Failed to load cubemap texture: " << fileName);
				LOG_HR(hr);
				return false;
			}

			return true;
		}




		ID3D11RasterizerState * D3d::CreateRasterizer(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode)
		{
			ID3D11RasterizerState* rasterState;
			D3D11_RASTERIZER_DESC rasterDesc;

			rasterDesc.AntialiasedLineEnable = false;
			rasterDesc.CullMode = cullMode;
			rasterDesc.DepthBias = 0;
			rasterDesc.DepthBiasClamp = 0.0f;
			rasterDesc.DepthClipEnable = false;
			rasterDesc.FillMode = fillMode;
			rasterDesc.FrontCounterClockwise = true;
			rasterDesc.MultisampleEnable = false;
			rasterDesc.ScissorEnable = false;
			rasterDesc.SlopeScaledDepthBias = 0.0f;

			ThomasCore::GetDevice()->CreateRasterizerState(&rasterDesc, &rasterState);

			return rasterState;
		}
	}
}