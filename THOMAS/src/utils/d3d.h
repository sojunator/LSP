#pragma once
#include "../Common.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <string>
#include "directXTK\WICTextureLoader.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "Dxguid.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace thomas 
{
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
			static bool LoadTextureFromFile(ID3D11Device* device, _In_opt_ ID3D11DeviceContext* context, std::string fileName, _Outptr_opt_ ID3D11Resource** texture, _Outptr_opt_ ID3D11ShaderResourceView** textureView, size_t size);
			static bool Destroy();
			static ID3D11Buffer* CreateVertexBuffer(UINT size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device);
			static ID3D11Buffer* CreateIndexBuffer(UINT size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA* data, ID3D11Device* device);
			static ID3D11Buffer* D3d::CreateBuffer(UINT size, bool dynamic, bool streamout, D3D11_SUBRESOURCE_DATA * data, ID3D11Device * device, D3D11_BIND_FLAG bindFlag);

			template<typename T>
			static ID3D11Buffer* CreateCBufferFromStruct(T dataStruct);

			template<typename T>
			static bool FillBuffer(ID3D11Buffer* buffer, T data);

		private:
			static ID3D11RenderTargetView* s_backBuffer;

		};
	}

}