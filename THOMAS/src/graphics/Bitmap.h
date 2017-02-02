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
			void CreateDepthStencilState();
			bool LoadTexture(std::string path);

		public:
			Bitmap(std::string path, std::string shaderName, int bitmapWidth, int bitmapHeight);
			~Bitmap();

			bool Initialize(int, int);
			int GetIndexCount();
			void Draw();
			bool Bind(int positionX, int positionY);
			bool Unbind();

		private:
			struct VertexType
			{
				math::Vector3 position;
				math::Vector2 texture;
			};

			struct BitmapData
			{
				ID3D11Buffer *vertexBuffer, *indexBuffer, *constantBuffer;
				int vertexCount, indexCount;
				ID3D11DepthStencilState* depthStencilState;
				Shader* shader;
				Texture* texture;
			};

			struct matrixStruct
			{
				math::Matrix orthMatrix;
			};

		private:
			int m_screenWidth, m_screenHeight;
			int m_bitmapWidth, m_bitmapHeight;
			int m_previousPosX, m_previousPosY;
			math::Matrix m_orthographic;
			BitmapData m_data;
			matrixStruct m_constBuffer;
		};
	}
}

