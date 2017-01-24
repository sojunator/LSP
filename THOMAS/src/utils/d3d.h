#pragma once
#include "../Common.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
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
			static bool SwapchainAndDevice(LONG witdh, LONG height, ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle);
			static bool CreateSwapChainTexture(ID3D11Device*& device, IDXGISwapChain*& swapchain);
			static void CreateViewPort(ID3D11DeviceContext*& context, LONG height, LONG width);

		public:
			static bool Init(LONG width, LONG height, ID3D11Device*& device, ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain, HWND handle);
			static void PresentBackBuffer(ID3D11DeviceContext*& context, IDXGISwapChain*& swapchain);
			static bool LoadTextureFromFile(ID3D11Device*& device, ID3D11DeviceContext*& context, wchar_t* fileName, _In_opt_ ID3D11Resource** texture, ID3D11ShaderResourceView** textureView, size_t size);
			static bool Destroy();
			static ID3D11Buffer* CreateVertexBuffer(UINT size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device);
			static ID3D11Buffer* CreateIndexBuffer(UINT size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device);
			static ID3D11Buffer* CreateBuffer(UINT size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA * data, ID3D11Device * device, D3D11_BIND_FLAG bindFlag);

			static ID3D11RasterizerState* CreateRasterizer();

			static bool Clear();

			template<typename T>
			static ID3D11Buffer* CreateCBufferFromStruct(T dataStruct);

			template<typename T>
			static bool FillBuffer(ID3D11Buffer* buffer, T data);



		private:
			static ID3D11RenderTargetView* s_backBuffer;
			static ID3D11RasterizerState* s_rasterState;

		};


		template<typename T>
		ID3D11Buffer* D3d::CreateCBufferFromStruct(T dataStruct)
		{
			ID3D11Buffer* buffer;
			D3D11_BUFFER_DESC bufferDesc;
			bufferDesc.ByteWidth = sizeof(dataStruct);
			bufferDesc.Usage = D3D11_USAGE_DEFAULT; //TODO: Maybe dynamic for map/unmap
			bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
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
	}

}