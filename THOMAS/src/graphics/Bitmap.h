#pragma once
#include "../utils/Math.h"
#include "Shader.h"
#include "../Window.h"

namespace thomas
{
	namespace graphics
	{
		class Texture;

		class Bitmap
		{
		private:
			bool InitializeBuffers(ID3D11Device*);
			void ShutdownBuffers();
			bool UpdateBuffers(ID3D11DeviceContext*, int, int);
			void RenderBuffers(ID3D11DeviceContext*);

			bool LoadTexture(ID3D11Device*, WCHAR*);
			void ReleaseTexture();

		public:
			Bitmap();
			~Bitmap();
			Bitmap(const Bitmap&);

			bool Initialize(ID3D11Device*, WCHAR*, int, int);
			void Shutdown();
			bool Render(ID3D11DeviceContext*, int, int);

			int GetIndexCount();
			ID3D11ShaderResourceView* GetTexture();

		private:
			struct VertexType
			{
				math::Vector3 position;
				math::Vector2 texture;
			};

			struct BitmapData
			{
				ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
				int m_vertexCount, m_indexCount;
				//TextureClass* m_Texture;
			};

		private:
			int m_screenWidth, m_screenHeight;
			int m_bitmapWidth, m_bitmapHeight;
			int m_previousPosX, m_previousPosY;
			BitmapData m_data;
			Window* m_window;
			Texture* m_texture;
		};
	}
}

