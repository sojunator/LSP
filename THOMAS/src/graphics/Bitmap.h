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
			bool InitializeBuffers();
			bool UpdateBuffers(int, int);
			void RenderBuffers();
			void CreateDepthStencilState();
			bool LoadTexture(std::string path);

		public:
			Bitmap();
			~Bitmap();

			bool Initialize(int, int, std::string);
			bool Render(int, int);
			int GetIndexCount();
			void Draw();
			bool Bind(math::Matrix viewMatrix, math::Matrix mvpMatrix);
			bool Unbind();

		private:
			struct VertexType
			{
				math::Vector3 position;
				math::Vector2 texture;
			};

			struct BitmapData
			{
				ID3D11Buffer *vertexBuffer, *indexBuffer;
				int vertexCount, indexCount;
				ID3D11DepthStencilState* depthStencilState;
				Shader* shader;
				Window* window;
				Texture* texture;
			};

		private:
			int m_screenWidth, m_screenHeight;
			int m_bitmapWidth, m_bitmapHeight;
			int m_previousPosX, m_previousPosY;
			BitmapData m_data;
		};
	}
}

