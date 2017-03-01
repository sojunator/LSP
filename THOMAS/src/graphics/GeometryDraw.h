#pragma once
#include "../Thomas.h"
namespace thomas
{
	namespace graphics
	{
		class GeometryDraw
		{
		public:
			GeometryDraw(math::Matrix worldMatrix);
			void SetShaders(std::string path, std::string shaderModel, std::string VSEntrypoint, _In_opt_ std::string GSEntryPoint, std::string PSEntryPoint);
			void DrawLine(math::Vector3 start, math::Vector3 end, math::Vector3 startColor, math::Vector3 endColor);
			void Update(object::component::Camera* camera);
		private:
			struct VertexData
			{
				math::Vector3 position;
				math::Vector3 color;
			};
			struct ConstantBuffer
			{
				math::Matrix worldMatrix;
				math::Matrix viewMatrix;
				math::Matrix projectionMatrix;
				math::Matrix  mvpMatrix;
			}m_cbData;
			ID3D11InputLayout* m_inputLayout;
			ID3D11VertexShader* m_vertexShader;
			ID3D11GeometryShader* m_geometryShader;
			ID3D11PixelShader* m_pixelShader;
			ID3D11Buffer* m_vertexBuffer;
			ID3D11Buffer* m_constantBuffer;
			std::vector<VertexData> m_data;
		};
	}
}