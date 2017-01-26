#pragma once
#include "../Common.h"
#include <string>
#include "../utils/d3d.h"
#include <vector>
namespace thomas
{
	namespace graphics
	{

		class THOMAS_API Shader
		{
		public:
			enum class InputLayouts
			{
				STANDARD = 0
			};
			enum class ResourceType
			{
				MVP_MATRIX = 0,
				MATERIAL = 1
			};
		private:

			ID3DBlob* Compile(std::string source, std::string profile, std::string main);
			bool CreateInputLayout(InputLayouts layout);

			Shader(std::string name, std::string filePath, InputLayouts inputLayout);
		public:



			~Shader();
			bool Bind();
			bool Unbind();
			std::string GetName();
			std::string GetFilePath();

			bool BindBuffer(ID3D11Buffer* resource, ResourceType type);
			bool BindBuffer(ID3D11Buffer* resource, int slot);
			bool BindTextures(ID3D11ShaderResourceView* texture, int slot);
			bool BindTextureSampler(ID3D11SamplerState* sampler, int slot);
			bool BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY type);
			bool BindVertexBuffer(ID3D11Buffer* vertexBuffer, UINT stride, UINT offset);
			bool BindIndexBuffer(ID3D11Buffer* indexBuffer);


			static Shader* CreateShader(std::string name, std::string filePath, InputLayouts inputLayout);
			static Shader* GetCurrentBoundShader();
			static Shader* GetShaderByName(std::string name);
			static bool Destroy();


		private:
			struct Data
			{
				ID3D11VertexShader* vertexShader;
				ID3D11PixelShader* pixelShader;
				ID3DBlob* vs;
				ID3D10Blob* ps;
				ID3D11InputLayout* inputLayout;
			};

			Data m_data;
			std::string m_name;
			std::string m_filePath;


			static Shader* s_currentBoundShader;

			static std::vector<Shader*> s_loadedShaders;



		};
	}
}