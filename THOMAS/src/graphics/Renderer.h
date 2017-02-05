#pragma once
#include "../Common.h"
#include "../utils/d3d.h"
#include "../utils/Math.h"
#include "../object/component/Camera.h"
#include "../object/component/Light.h"

namespace thomas {
	namespace graphics
	{
		class THOMAS_API Renderer {
		private:
			
		public:

			struct GameObjectBuffer
			{
				math::Matrix worldMatrix;
				math::Matrix viewMatrix;
				math::Matrix projectionMatrix;
				math::Matrix mvpMatrix;
				math::Vector3 camPos;
				float buffer;
			};


			static bool Init();

			static void Clear();
			static void Render();

			static bool Destroy();

			static std::vector<object::component::Camera*> GetCameras();

			static void BindGameObjectBuffer(object::component::Camera* camera, object::GameObject* gameObject);

			static ID3D11ShaderResourceView* GetDepthBufferSRV();

		private:
			static ID3D11RenderTargetView* s_backBuffer;
			static ID3D11ShaderResourceView* s_backBufferSRV;
			static ID3D11RasterizerState* s_rasterState;
			static ID3D11DepthStencilState* s_depthStencilState;
			static ID3D11DepthStencilView* s_depthStencilView;
			static ID3D11ShaderResourceView* s_depthBufferSRV;

			static ID3D11Buffer* s_objectBuffer;
			static GameObjectBuffer s_objectBufferStruct;
		};
	}
}