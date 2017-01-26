#pragma once
#include "../Common.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include <vector>
#include "directXTK\WICTextureLoader.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "Dxguid.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace thomas {
	namespace utils
	{
		
		class THOMAS_API D3d
		{
		private:
			static bool CreateSwapchainAndDeviceAndContext(LONG witdh, LONG height, ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle);
			static bool CreateSwapChainTexture(ID3D11Device*& device, IDXGISwapChain*& swapchain);
			static void CreateViewPort(ID3D11DeviceContext*& context, LONG height, LONG width);
			static bool CreateDepthStencilState(ID3D11Device* device, ID3D11DepthStencilState*& stencil);
			static bool CreateDepthStencilView(ID3D11Device* device, ID3D11DepthStencilView *& stencilView, ID3D11Texture2D*& texture);
			


			static ID3D11Debug* CreateDebug();
		public:
			static bool Init(ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, ID3D11Debug*& debug);
			static void PresentBackBuffer(ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain);
			static bool LoadTextureFromFile(ID3D11Device*& device, ID3D11DeviceContext*& context, wchar_t* fileName, _In_opt_ ID3D11Resource** texture, ID3D11ShaderResourceView** textureView, size_t size);
			static bool Destroy();
			static ID3D11RenderTargetView* CreateRenderTargetView(ID3D11Resource* buffer);

			static ID3D11RasterizerState* CreateRasterizer();

			static bool Clear();

			template<typename T>
			static ID3D11Buffer* CreateBufferFromStruct(T& dataStruct, D3D11_BIND_FLAG bindFlag);

			template <typename T>
			static ID3D11Buffer* CreateBufferFromVector(const std::vector<T>& vectorData, D3D11_BIND_FLAG bindFlag);

			template<typename T>
			static bool FillBuffer(ID3D11Buffer* buffer, T data);




		private:
			static ID3D11RenderTargetView* s_backBuffer;
			static ID3D11RasterizerState* s_rasterState;


		};


		template<typename T>
		ID3D11Buffer* D3d::CreateBufferFromStruct(T& dataStruct, D3D11_BIND_FLAG bindFlag)
		{
			ID3D11Buffer* buffer;
			D3D11_BUFFER_DESC bufferDesc;
			bufferDesc.ByteWidth = sizeof(dataStruct);
			bufferDesc.Usage = D3D11_USAGE_DEFAULT; //TODO: Maybe dynamic for map/unmap
			bufferDesc.BindFlags = bindFlag;
			bufferDesc.CPUAccessFlags = 0; //CPU if dynamic
			bufferDesc.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = &dataStruct;
			InitData.SysMemPitch = 0;
			InitData.SysMemSlicePitch = 0;

			HRESULT result = ThomasCore::GetDevice()->CreateBuffer(&bufferDesc, &InitData, &buffer);

			if (result != S_OK)
				LOG(result);

			if (result == S_OK)
				return buffer;

			return NULL;

		}
		template<typename T>

		bool D3d::FillBuffer(ID3D11Buffer* buffer, T data)
		{
			ThomasCore::GetDeviceContext()->UpdateSubresource(buffer, 0, 0, &data, 0, 0);
			return true;
		}


		template <typename T>
		ID3D11Buffer* D3d::CreateBufferFromVector(const std::vector<T>& vectorData, D3D11_BIND_FLAG bindFlag)
		{
			ID3D11Buffer* buffer;
			D3D11_BUFFER_DESC bufferDesc;
			bufferDesc.ByteWidth = sizeof(vectorData[0]) * vectorData.size();
			bufferDesc.Usage = D3D11_USAGE_DEFAULT; //TODO: Maybe dynamic for map/unmap
			bufferDesc.BindFlags = bindFlag;
			bufferDesc.CPUAccessFlags = 0; //CPU if dynamic
			bufferDesc.MiscFlags = 0;
			

			const T* data = &vectorData[0];

			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = data;
			InitData.SysMemPitch = 0;
			InitData.SysMemSlicePitch = 0;

			HRESULT result = ThomasCore::GetDevice()->CreateBuffer(&bufferDesc, &InitData, &buffer);

			if (result != S_OK)
				LOG(result);

			if (result == S_OK)
				return buffer;

			return NULL;

		}
	}

}